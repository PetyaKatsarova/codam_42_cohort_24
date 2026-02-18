Redis = Remote Dictionary Server

In-memory database (stores data in RAM, not disk)
Key-value store (like JavaScript objects: {key: value})
Blazing fast (sub-millisecond response times)

Without cache:
User requests page → 
  Database query (50ms) → 
  Process data (20ms) → 
  Return response
= 70ms per request

1000 users = 70 seconds of DB load

With Redis Cache:
-------------------------------------------
1. redis_cache container:
This is your standalone Redis server. It runs the Redis database, which is a fast, in-memory key-value store. Other services (like WordPress) connect to it to store and retrieve cached data.

2. Redis in WordPress:
You installed the Redis Cache plugin in WordPress. This plugin lets WordPress use Redis (the redis_cache container) to cache database queries, objects, and other data, making your site faster by reducing database load.

3. redis volume:
This Docker volume is attached to your redis_cache container. It stores Redis’ persistent data (the actual key-value database files). This way, if the container restarts or is recreated, your cached data isn’t lost.


redis_cache = runs Redis server
Redis plugin in WordPress = lets WordPress use Redis for caching
redis volume = stores Redis data on disk for persistence
-----------------------------------------------
Without Redis:
User → Nginx → WordPress → MySQL (50ms query) → Response

With Redis:
User → Nginx → WordPress → Redis (0.1ms lookup) → Response
                          ↓ (if miss)
                        MySQL (50ms) → Store in Redis














------------------------------------

Common Use Cases
1. Session Storage
// Store user login sessions
redis.set('session:user123', JSON.stringify({
  userId: 123,
  username: 'alice',
  loggedInAt: Date.now()
}), 'EX', 3600);  // Expires in 1 hour

2. Database Query Cache
// Cache expensive queries
const cacheKey = 'users:all';
let users = await redis.get(cacheKey);
redis:
    build: ./requirements/bonus/redis_cache
    container_name: redis
    volumes:
      - redis_data:/data
    networks:
      - inception
    restart: unless-stopped
if (!users) {
  // Cache miss - query database
  users = await db.query('SELECT * FROM users');
  await redis.set(cacheKey, JSON.stringify(users), 'EX', 300);  // 5 min
}

3. Rate Limiting
// Limit API requests per user
const key = `ratelimit:${userId}`;
const requests = await redis.incr(key);  // Increment counter

if (requests === 1) {
  await redis.expire(key, 60);  // Reset after 60 seconds
}

if (requests > 100) {
  throw new Error('Rate limit exceeded');
}

4. Real-time Leaderboards
// Gaming scores
await redis.zadd('leaderboard', 1500, 'player1');  // Score: 1500
await redis.zadd('leaderboard', 2000, 'player2');

const topPlayers = await redis.zrevrange('leaderboard', 0, 9);  // Top 10
```

---

## Part 3: Docker Setup for Inception

### Directory Structure
```
inception/
├── srcs/
│   ├── requirements/
│   │   ├── nginx/
│   │   ├── wordpress/
│   │   ├── mariadb/
│   │   └── redis/              ← NEW
│   │       ├── Dockerfile
│   │       ├── conf/
│   │       │   └── redis.conf
│   │       └── tools/
│   │           └── setup.sh
│   └── docker-compose.yml
└── Makefile

Redis Configuration Explained
Yes, that's the complete redis.conf file. Here's what each line means:

Network Settings
confbind 0.0.0.0
Meaning: Accept connections from any IP address
Why: Docker containers need to connect from different IPs
Alternative: bind 127.0.0.1 (only localhost, won't work in Docker)
confport 6379
Meaning: Redis listens on port 6379
Why: Default Redis port
confprotected-mode no
Meaning: Disable protection (no password required)
Why: Trust Docker network (containers only)
Production: Set to yes and add password

Memory Management
confmaxmemory 256mb
Meaning: Redis can use maximum 256 megabytes of RAM
Why: Prevent Redis from consuming all server memory
Adjust: Increase if you have more data (512mb, 1gb)
confmaxmemory-policy allkeys-lru
Meaning: When memory is full, delete Least Recently Used keys
Options:

allkeys-lru - Delete oldest accessed keys (good for cache)
noeviction - Return errors when full (good for persistent data)
allkeys-random - Delete random keys


Persistence (Data Saving)
RDB Snapshots
confsave 900 1
Meaning: Save to disk if 1 key changed in last 900 seconds (15 minutes)
confsave 300 10
Meaning: Save to disk if 10 keys changed in last 300 seconds (5 minutes)
confsave 60 10000
Meaning: Save to disk if 10,000 keys changed in last 60 seconds (1 minute)
Why these numbers?

Light usage: Save every 15 min
Medium usage: Save every 5 min
Heavy usage: Save every 1 min

Result: Creates dump.rdb file for crash recovery
AOF (Append Only File)
confappendonly yes
Meaning: Enable AOF persistence (logs every write command)
Why: More durable than RDB (loses less data on crash)
confappendfilename "appendonly.aof"
Meaning: Name of the AOF file
confappendfsync everysec
Meaning: Sync AOF to disk every second
Options:

always - Sync after every write (slow, safest)
everysec - Sync every second (balanced) ✓
no - Let OS decide (fast, risky)
--------------------------------------------------------------


Redis Test Results - Complete Analysis
✅ YES, Redis is Working! Here's the Proof:

1. Connection Status
Status: Connected
Client: PhpRedis (v6.2.0)
Drop-in: Valid
Disabled: No
Proof:

✅ WordPress connected to Redis
✅ Using fast PhpRedis extension
✅ Cache interceptor active ("Drop-in: Valid")
✅ Caching enabled ("Disabled: No")


2. Cached Keys (THE SMOKING GUN)
13 cached keys found:
- wp:options:alloptions
- wp:translation_files:...
- wp:transient:doing_cron
- wp:redis-cache:metrics
This proves:

✅ WordPress IS storing data in Redis
✅ alloptions = entire settings table cached (HUGE win)
✅ Translation files cached (faster page loads)
✅ Transients cached (temporary data)

Without Redis: These would be in MySQL database (slow)
With Redis: In RAM (100x faster)

3. What Each Cached Key Does
KeyWhat It CachesPerformance Impactwp:options:alloptionsAll WordPress settingsMASSIVE - avoids 100+ DB querieswp:translation_files:*Language/translation dataMedium - faster for multilingual siteswp:transient:doing_cronScheduled tasks statusSmall - reduces DB writeswp:site-transient:*Theme/plugin patternsMedium - faster admin panelwp:redis-cache:metricsCache statisticsSmall - tracks performance









