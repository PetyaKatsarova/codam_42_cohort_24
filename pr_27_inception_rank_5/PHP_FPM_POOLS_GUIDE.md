# PHP-FPM Pools - Complete Guide

## **What is a Pool?**

A **pool** is an independent group of PHP-FPM worker processes with their own configuration, listening port, and resource limits.

Think of it like:
```
PHP-FPM Server
├── Pool [www]         ← Group 1: Website
│   ├── Worker 1
│   ├── Worker 2
│   └── Worker 3
│
├── Pool [api]         ← Group 2: API
│   ├── Worker A
│   └── Worker B
│
└── Pool [cron]        ← Group 3: Scheduled tasks
    └── Worker X
```

Each pool:
- Listens on its own port or socket
- Has its own process manager settings
- Has its own resource limits
- Has its own configuration

---

## **Why Use Multiple Pools?**

Different applications have **different needs**:

### **Scenario 1: Website Pool**
```ini
[www]
listen = 0.0.0.0:9000
pm.max_children = 10
pm.start_servers = 5
```
- Gets lots of traffic
- Needs 10 workers to handle load
- Starts 5 workers upfront

### **Scenario 2: API Pool**
```ini
[api]
listen = 0.0.0.0:9001
pm.max_children = 3
pm.start_servers = 1
```
- Gets light traffic
- Only needs 3 workers
- Starts with just 1

### **Scenario 3: Admin Panel Pool**
```ini
[admin]
listen = 0.0.0.0:9002
pm.max_children = 2
pm = static
```
- Very few admins access it
- Fixed 2 processes (no scaling)
- Predictable behavior

### **Scenario 4: Cron Jobs Pool**
```ini
[cron]
listen = /run/php/cron.sock
pm.max_children = 1
pm = static
```
- Only 1 scheduled task at a time
- Uses Unix socket (not TCP port)
- Never scales

---

## **Pool Configuration Options**

### **1. Listening Address**

**TCP Port:**
```ini
[www]
listen = 0.0.0.0:9000      # Listen on all IPs, port 9000
listen = 127.0.0.1:9000    # Listen only on localhost
listen = 192.168.1.5:9000  # Listen on specific IP
```

**Unix Socket (faster, no network overhead):**
```ini
[www]
listen = /run/php/www.sock
listen.owner = www-data
listen.group = www-data
listen.mode = 0660
```

**Why different addresses?**
- `0.0.0.0:9000` = Accept from any IP (Nginx from any interface)
- `127.0.0.1:9000` = Only localhost (more secure if Nginx on same machine)
- `/run/php/www.sock` = Unix socket (fastest, no TCP overhead)

---

### **2. User and Group**

```ini
[www]
user = www-data        # Process runs as www-data user
group = www-data       # Process runs as www-data group

listen.owner = www-data
listen.group = www-data
listen.mode = 0666     # Socket permissions (rw-rw-rw-)
```

**Why?**
- Security: Processes don't run as root
- File access: Can read/write web files (owned by www-data)
- Isolation: Limited permissions if hacked

**Example:**
```bash
# If user = www-data:
ls -l /var/www/html/index.php
# Output: -rw-r--r-- www-data www-data index.php
#         ↑ www-data can read/write
#         www-data process can access this file
```

---

### **3. Process Manager (pm)**

#### **Option A: `pm = static`**
```ini
[www]
pm = static
pm.max_children = 5
```

**Behavior:**
- Always runs exactly 5 processes
- Processes never scale up/down
- 5 processes always consuming memory

**When to use:**
- Predictable traffic
- Fixed server capacity
- Dedicated servers with lots of RAM

**Pros:**
- Predictable performance
- Simple management
- No scaling overhead

**Cons:**
- Wastes memory in low traffic
- Can't handle traffic spikes
- Fixed resource usage

---

#### **Option B: `pm = dynamic`** (What we use)
```ini
[www]
pm = dynamic
pm.max_children = 5
pm.start_servers = 2
pm.min_spare_servers = 1
pm.max_spare_servers = 3
```

**How it works:**

| Metric | Meaning |
|--------|---------|
| `pm.start_servers = 2` | Start with 2 processes when pool boots |
| `pm.min_spare_servers = 1` | If less than 1 idle → keep 1 |
| `pm.max_spare_servers = 3` | If more than 3 idle → kill extras |
| `pm.max_children = 5` | Never exceed 5 processes total |

**Visual Timeline:**

```
Time 1 (No traffic):
  Processes: 1 (min_spare)
  Memory: Low

Time 2 (Light traffic):
  Processes: 2 (start_servers)
  Memory: Normal

Time 3 (Heavy traffic):
  Requests come in → Need more processes
  Processes: 3, 4, 5 (scale up to max)
  Memory: Higher

Time 4 (Traffic drops):
  Idle processes detected
  Kill extras back to max_spare_servers = 3
  Processes: 3

Time 5 (Very low traffic):
  More idle processes killed
  Processes: 1 (min_spare)
  Memory: Low again
```

**When to use:**
- Variable traffic (most web apps)
- Shared hosting
- Development
- Cost-conscious hosting

**Pros:**
- Scales with traffic
- Saves memory when quiet
- Handles spikes

**Cons:**
- Slight overhead creating processes
- Less predictable performance

---

#### **Option C: `pm = ondemand`**
```ini
[www]
pm = ondemand
pm.max_children = 5
pm.process_idle_timeout = 10s
```

**How it works:**
- Starts 0 processes initially
- Creates processes **only when requests arrive**
- Kills unused processes after timeout

**Timeline:**

```
Idle (no traffic):
  Processes: 0
  Memory: Minimal

Traffic arrives:
  Create process 1
  Create process 2
  Create process 3

30 seconds of no traffic:
  Processes 1,2,3 idle for 10s → killed
  Processes: 0
  Memory: Minimal again
```

**When to use:**
- Very low traffic sites
- Development machines
- Serverless environments
- Shared hosting (save memory)

**Pros:**
- Minimal memory usage
- Perfect for idle periods
- Highly efficient

**Cons:**
- Latency spike when requests arrive (create process)
- Not good for constant traffic

---

### **4. Process Request Limits**

```ini
[www]
pm.max_requests = 500
pm.max_spawn_rate = 32
```

**`pm.max_requests = 500`:**
- Recycle process after 500 requests
- Prevents memory leaks
- Example:
  ```
  Process 1: Handles requests 1-500 → Recycled
  Process 1 (new): Handles requests 501-1000 → Recycled
  ```

**Why?** PHP scripts can have memory leaks. Recycling kills leaked memory.

**`pm.max_spawn_rate = 32`:**
- Maximum processes to create per second
- Prevents sudden memory spike
- Prevents fork bombs

---

### **5. Timeouts**

```ini
[www]
request_terminate_timeout = 30s
request_slowlog_timeout = 5s
process_idle_timeout = 10s
```

**`request_terminate_timeout = 30s`:**
- Kill request if it takes longer than 30 seconds
- Prevents hung processes
- Prevents memory buildup

**`request_slowlog_timeout = 5s`:**
- Log requests taking longer than 5 seconds
- Find performance issues

**`process_idle_timeout = 10s`:**
- Only used with `pm = ondemand`
- Kill process if idle for 10 seconds

---

### **6. Logging**

```ini
[www]
access.log = /var/log/php-fpm/access.log
slowlog = /var/log/php-fpm/slow.log
```

**Access log:** Every request
```
10.0.0.1 - 10/Feb/2026 12:34:56 +0000 "GET /index.php" 200 1234 0.521
```

**Slow log:** Requests taking time
```
[10-Feb-2026 12:34:56] [pool www] pid 1234
script_filename = /var/www/html/slow-page.php
function = db_query() line 42
took 5.123 sec
```

---

## **Real-World Examples**

### **Example 1: Small WordPress Site**

Single pool, handles everything:

```ini
[www]
listen = 0.0.0.0:9000
user = www-data
group = www-data
pm = dynamic
pm.max_children = 5
pm.start_servers = 2
pm.min_spare_servers = 1
pm.max_spare_servers = 3
pm.max_requests = 500
```

**Setup:**
```
Nginx (port 443)
    ↓
PHP-FPM [www] (port 9000)
    ├── Process 1
    ├── Process 2
    └── Process 3-5 (on demand)
    ↓
WordPress
```

---

### **Example 2: Complex Application (Website + API)**

Two pools for different needs:

**Pool 1: Website**
```ini
[www]
listen = 0.0.0.0:9000
pm = dynamic
pm.max_children = 10
pm.start_servers = 5
```

**Pool 2: API**
```ini
[api]
listen = 0.0.0.0:9001
pm = dynamic
pm.max_children = 3
pm.start_servers = 1
```

**Setup:**
```
Nginx (port 443)
    ├─ /           → PHP-FPM [www] (9000)
    │                Website pool (5-10 processes)
    │
    └─ /api/       → PHP-FPM [api] (9001)
                     API pool (1-3 processes)
```

**Why separate?**
- Website gets heavy traffic → 10 max
- API gets light traffic → 3 max
- Isolated resource management
- If API crashes, website still runs

---

### **Example 3: High-Traffic Site with Admin**

Three pools for different priorities:

```ini
[www]
listen = 0.0.0.0:9000
pm = dynamic
pm.max_children = 50        # Many users
pm.start_servers = 10

[admin]
listen = 0.0.0.0:9001
pm = static
pm.max_children = 5         # Few admins, static

[cron]
listen = /run/php/cron.sock
pm = static
pm.max_children = 1         # Only one cron at a time
```

---

## **Pool Lifecycle**

### **Step 1: Boot**
```ini
pm.start_servers = 2
```
Creates 2 processes immediately

### **Step 2: Low Traffic**
```
Requests < min_spare_servers
Keep killing extras until: pm.min_spare_servers = 1
```

### **Step 3: High Traffic**
```
New request arrives
No spare processes available
Create new process (until pm.max_children)
```

### **Step 4: Traffic Drop**
```
Idle processes detected
If idle > pm.max_spare_servers
Kill excess processes
```

### **Step 5: Recycling**
```
Process handles 500 requests (pm.max_requests)
Process recycled (killed and recreated)
Clears memory leaks
```

---

## **Pool Monitoring**

### **See Running Pools**
```bash
ps aux | grep php-fpm
# output:
# root     1234 0.0 0.5 123456 45678 ? Ss 12:34 0:00 php-fpm: master process
# www-data 1235 0.0 0.6 234567 56789 ? S  12:34 0:00 php-fpm: pool www
# www-data 1236 0.0 0.6 234567 56789 ? S  12:34 0:00 php-fpm: pool www
```

### **Check Status**
```bash
# Enable status page in pool config:
pm.status_path = /status

# Access in Nginx:
curl http://localhost/status
```

Output:
```
pool:                 www
process manager:      dynamic
start time:           10/Feb/2026 12:34:56 +0000
start since:          3600
accepted conn:        1234
listen queue:         0
max listen queue:     5
listen queue len:     128
idle processes:       2
active processes:     1
total processes:      3
max children reached: 0
slow requests:        0
```

---

## **Best Practices**

### **1. Dynamic for Most Cases**
```ini
pm = dynamic    # Default choice
```

### **2. Calculate max_children**
```
Formula: (Available RAM - System RAM) / (Per-process RAM)

Example:
Server RAM: 2GB
System uses: 512MB available
Per-process RAM: 50MB (WordPress)

max_children = (2000 - 512) / 50 = 29
# But use 10-20 to be safe
```

### **3. Set Realistic start_servers**
```ini
pm.start_servers = 4       # Not too low (slow startup)
                           # Not too high (wastes RAM at start)
```

### **4. Monitor Memory**
```bash
# Watch memory usage
watch -n 1 'ps aux | grep php-fpm | tail -5'
```

### **5. Log Slow Requests**
```ini
slowlog = /var/log/php-fpm/slow.log
request_slowlog_timeout = 5s
```

### **6. Use Unix Socket if Local**
```ini
# Instead of TCP:
listen = 0.0.0.0:9000

# Use socket (faster, no network overhead):
listen = /run/php/www.sock
```

---

## **Summary**

| Aspect | Details |
|--------|---------|
| **What** | Group of PHP-FPM processes with config |
| **Why** | Different apps need different resources |
| **pm = static** | Fixed process count (predictable) |
| **pm = dynamic** | Scale based on load (smart) |
| **pm = ondemand** | Create on demand (minimal memory) |
| **Listening** | TCP port or Unix socket |
| **Security** | Always run as unprivileged user |
| **Monitoring** | Check status, logs, memory usage |

**In Your WordPress:**
- 1 pool `[www]` on port 9000
- `pm = dynamic` scales 1-5 workers
- Runs as `www-data` user
- Recycles every 500 requests

🎯 **Pools allow fine-grained control over PHP process management!**
