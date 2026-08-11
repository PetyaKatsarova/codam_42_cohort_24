# Architecture & API Flow — 42Overflow

## Services

Nine containers run under Docker Compose on a single shared `app-net` network. Only two ports are exposed to the host.

| Service | Image / Build | Internal port | Host port | Role |
|---------|--------------|---------------|-----------|------|
| `caddy` | `caddy:2.9-alpine` | 443 | **8443** | HTTPS reverse proxy (TLS termination) |
| `app` | `./Dockerfile.dev` | 5173 | — | SvelteKit frontend + backend API |
| `llm-server` | `./llm-system-interface` | 8081 | — | Go LLM gateway (Gemini / Ollama / RAG) |
| `python-rag` | `./python-services/rag` | 8090 | — | Python RAG service (embeddings + retrieval) |
| `python-stt` | `./python-services/speech-to-text` | 8091 | — | Python speech-to-text (faster-whisper) |
| `ollama` | `ollama/ollama:0.20.5` | 11434 | — | Local LLM server (Gemma3:4b + nomic-embed-text) |
| `ollama-init` | `./ollama-init` | — | — | One-shot init: pulls model weights into Ollama |
| `chromadb` | `chromadb/chroma:0.5.5` | 8000 | — | Vector store for RAG embeddings |
| `postgres` | `postgres:15.13` | 5432 | **5433** | Primary database |

> All inter-service traffic stays inside `app-net`. The browser can only reach `caddy:8443`.

---

## Startup Order

```
ollama ──────────────────────────────────────────────────┐
                                                         ▼
ollama-init ──────────────────────────────────────► llm-server ──┐
                                                                  │
chromadb ──────────────────────────────────────────► python-rag ─┤
                                                                  │
postgres ──────────────────────────────────────────► app ◄───────┘
                                                      │
                                                      ▼
                                                    caddy
```

`ollama-init` runs once (pulls model weights), then exits successfully. Every other service waits on `service_healthy` or `service_completed_successfully` before starting.

---

## Service Map

```
                        ┌─────────────────────────────────────────┐
                        │              app-net (Docker)            │
                        │                                          │
 Browser                │  ┌────────┐      ┌──────────────────┐   │
 https://localhost:8443 │  │        │─────►│   app (SvelteKit) │  │
        │               │  │ caddy  │      │   :5173           │  │
        └──────────────►│  │ :8443  │      └────────┬──────────┘  │
                        │  │        │               │              │
                        │  └────────┘      ┌────────▼──────────┐  │
                        │                  │  postgres          │  │
                        │                  │  :5432             │  │
                        │                  └───────────────────-┘  │
                        │                                          │
                        │  ┌─────────────────┐  ┌─────────────┐  │
                        │  │  llm-server (Go) │  │ python-stt  │  │
                        │  │  :8081           │  │ :8091       │  │
                        │  └────┬────────┬────┘  └─────────────┘  │
                        │       │        │                         │
                        │  ┌────▼──┐  ┌──▼───────────┐            │
                        │  │ollama │  │ python-rag    │            │
                        │  │:11434 │  │ :8090         │            │
                        │  └───────┘  └──────┬────────┘            │
                        │                    │                     │
                        │             ┌──────▼──────┐             │
                        │             │  chromadb   │             │
                        │             │  :8000      │             │
                        │             └─────────────┘             │
                        └─────────────────────────────────────────┘
```

---

## API Flows

### 1. Standard page / data request

```
Browser → HTTPS :8443 → caddy → app:5173 (SvelteKit SSR) → postgres:5432 (Prisma)
                                         └──────────────────────────────────────────►
                                         ◄──────────────────────────────────────────┘
                                ◄──────────
         ◄──────────────────────
```

SvelteKit handles both the HTML render and REST/form API routes. Prisma talks to Postgres directly inside the same container.

---

### 2. AI Assist — Gemini (cloud LLM)

```
Browser
  │  POST /api/ai/gemini  { messages: [...] }
  ▼
caddy → app:5173
  │  internal call  POST llm-server:8081/api/ai/gemini
  ▼                 Header: X-Internal-Secret
llm-server (Go)
  │  validates → rate-limits → builds prompt
  │  POST https://generativelanguage.googleapis.com/...  (Gemini API, external)
  ▼
Gemini API
  │  SSE stream chunks back
  ▼
llm-server → SSE stream → app → SSE stream → Browser
```

---

### 3. AI Assist — Ollama (local Gemma3:4b)

```
Browser
  │  POST /api/ai/ollama  { messages: [...] }
  ▼
caddy → app:5173
  │  internal call  POST llm-server:8081/api/ai/ollama
  ▼                 Header: X-Internal-Secret
llm-server (Go)
  │  validates → rate-limits → queued (semaphore, 1 request at a time)
  │  POST ollama:11434/api/chat  (internal)
  ▼
ollama (Gemma3:4b)
  │  SSE stream chunks back
  ▼
llm-server → SSE stream → app → SSE stream → Browser
```

> Ollama is CPU-bound. A buffered channel (capacity 1) serialises requests to prevent resource exhaustion. Requests wait up to 30 s before receiving a 503.

---

### 4. AI Assist — RAG / Community mode

```
Browser
  │  POST /api/ai/community  { messages: [...] }
  ▼
caddy → app:5173
  │  internal call  POST llm-server:8081/api/ai/community
  ▼                 Header: X-Internal-Secret
llm-server (Go)
  │  checks in-memory cache for this question
  │  (cache miss) POST python-rag:8090/rag/retrieve  { question }
  │               Header: X-Admin-Token
  ▼
python-rag
  │  hybrid_search: BM25Plus + fastembed cosine similarity (NumPy)
  │  returns top-k context chunks + confidence score
  ▼
llm-server (Go)
  │  injects context into system prompt
  │  calls Gemini or Ollama (same flow as above)
  │  caches the response
  ▼
SSE stream → app → Browser
```

---

### 5. Voice / Speech-to-text

```
Browser (MediaRecorder API)
  │  POST /api/speech  audio blob (WAV, max 10 MB)
  ▼
caddy → app:5173
  │  internal call  POST python-stt:8091/convert_audio
  ▼
python-stt (faster-whisper)
  │  saves blob to temp file → transcribes on CPU → deletes temp file
  │  returns { "text": "..." }
  ▼
app → Browser (text inserted into AI Assist input)
  │  (user confirms and submits → triggers flow 2, 3, or 4 above)
```

---

## Admin Flows

All admin endpoints on `python-rag:8090` require `X-Admin-Token` header.  
All endpoints on `llm-server:8081` require `X-Internal-Secret` header.  
Full implementation: `python-services/rag/router_admin.py`

### Seed test data into Postgres then sync to RAG

```
Admin
  │  POST python-rag:8090/admin/seed-postgres[?clean=true]
  ▼
python-rag
  │  inserts fake users / subjects / posts / comments via asyncpg
  │  (does NOT touch the RAG index)
  ▼
Admin
  │  POST python-rag:8090/admin/sync-chroma   ← all data (real + fake)
  │  — or —
  │  POST python-rag:8090/admin/sync-real     ← real posts only, excludes fake users
  ▼
python-rag
  │  reads posts from postgres
  │  → checks ChromaDB hashes — only re-embeds new/changed docs (ollama nomic-embed-text)
  │  → upserts new embeddings to ChromaDB (persistent store)
  │  → fetches all embeddings from ChromaDB → rebuilds NumPy index + BM25 index in memory
  │  → calls llm-server:8081/admin/clear-rag-cache  (invalidates stale cached answers)
  ▼
llm-server
  │  clears in-memory RAG response cache
```

### Wipe all data and reset

```
Admin
  │  POST python-rag:8090/admin/wipe
  ▼
python-rag
  │  deletes from Postgres: Like, SubjectMember, Comment, Post, Subject
  │  clears ChromaDB collection
  │  rebuilds in-memory indexes from seed data only (service stays healthy)
```

### Helper script

`./reload_rag.sh` is a convenience wrapper that calls `/admin/sync-real`.

### Metrics

```
GET python-rag:8090/admin/metrics  →  { uptime_seconds, corpus_size, last_sync_at,
                                         retrieve_total, retrieve_errors, bm25_only_fallbacks }
```

---

## Data Volumes

| Volume | Used by | Contents |
|--------|---------|----------|
| `postgres-data` | postgres | All application data |
| `ollama-data` | ollama | Downloaded model weights |
| `chroma-data` | chromadb | Persisted vector embeddings |
| `uploads-data` | app | User-uploaded images |
| `whisper-model-cache` | python-stt | faster-whisper model weights |
| `caddy-data` / `caddy-config` | caddy | TLS certificates (prevents browser warnings on restart) |

---

## What Other Docs Are Typically in a Project

For reference, standard docs folders usually contain:

| File | Purpose |
|------|---------|
| `architecture.md` ← this file | Services, ports, API flows, data flows |
| `api-reference.md` | Every endpoint: method, path, headers, request body, response shape, error codes |
| `dev-setup.md` | How to run the project locally without Docker (individual services, test commands) |
| `env-reference.md` | Every environment variable across all `.env` files: name, required/optional, default, description |
| `testing.md` | How to run the test suite, what is covered, how to add tests |
| `troubleshooting.md` | Common errors and fixes (e.g. Ollama OOM, ChromaDB not ready, Prisma migration drift) |
| `decisions.md` (ADR) | Architecture Decision Records — why ChromaDB retrieval was replaced with NumPy (CPU speed), why Go for the gateway, etc. |
| `glossary.md` | Definitions for project-specific terms (RAG, BM25, SSE, hybrid retrieval, etc.) |