# WordPress Container Complete Guide - Entrypoint, Installation, Volumes & Images

## **Part 1: What is entrypoint.sh?**

**entrypoint.sh** is a **script that runs automatically when the container starts**.

Think of it like:
```
Container boots up
    ↓
Docker runs entrypoint.sh
    ↓
Script does setup tasks
    ↓
Script starts the main application (PHP-FPM)
```

---

### **Breaking Down Each Step**

#### **STEP 1: Wait for MariaDB (Lines 1-14)**

```bash
echo "WordPress: Waiting for MariaDB..."
RETRIES=0
until nc -z mariadb 3306 2>/dev/null; do
    RETRIES=$((RETRIES + 1))
    if [ $RETRIES -gt 60 ]; then
        echo "WordPress: ERROR - MariaDB timeout"
        exit 1
    fi
    sleep 1
done
```

**What it does:**
- Uses `nc` (netcat) to check if MariaDB port 3306 is open
- Keeps checking every 1 second
- Times out after 60 seconds
- Exits with error if database never becomes ready

**Why?**
- WordPress NEEDS a database to work
- If we start PHP-FPM before DB is ready, it crashes
- This ensures database is running first

**Visual:**

```
Container starts
    ↓
entrypoint.sh runs
    ↓
Check if MariaDB is ready? NO → Wait 1 second
Check if MariaDB is ready? NO → Wait 1 second
Check if MariaDB is ready? YES → Continue!
    ↓
Proceed to Step 2
```

---

#### **STEP 2: Download and Install WordPress (Lines 15-30)**

```bash
if [ ! -f "/var/www/html/wp-load.php" ]; then
    echo "WordPress: Installing WordPress..."
    cd /var/www/html
    wget -q https://wordpress.org/latest.tar.gz -O /tmp/wordpress.tar.gz
    tar xzf /tmp/wordpress.tar.gz
    mv wordpress/* .
    rm -rf wordpress /tmp/wordpress.tar.gz
fi
```

**What each command does:**

| Command | What | Why |
|---------|------|-----|
| `[ ! -f wp-load.php ]` | Check if WordPress file exists | Skip download if already installed |
| `wget latest.tar.gz` | Download WordPress from internet | Get latest version from wordpress.org |
| `tar xzf` | Extract compressed file | Access WordPress files |
| `mv wordpress/* .` | Move files to current directory | WordPress goes in `/var/www/html` |
| `rm -rf wordpress` | Delete empty directory | Clean up |

**How it works:**

```
First Container Start:
    ↓
wp-load.php doesn't exist
    ↓
Download WordPress (large file, ~20MB)
    ↓
Extract files
    ↓
Files now in /var/www/html/
    ↓
Container restarts later:
    ↓
wp-load.php EXISTS (from volume)
    ↓
Skip download, reuse existing files
    ↓
Much faster startup!
```

**Where do files go?**

```
Container folder:      /var/www/html/
    ↓
Mounted to:            ~/data/wordpress (on your computer)
    ↓
Persists across        Container restarts
```

---

#### **STEP 3: Fix File Permissions (Lines 31-35)**

```bash
echo "WordPress: Setting permissions..."
chown -R www-data:www-data /var/www/html
chmod 755 /var/www/html
```

**What it does:**

| Command | What |
|---------|------|
| `chown -R www-data` | Change owner to www-data user |
| `chmod 755` | Set permissions: rwxr-xr-x |

**Why?**

WordPress files are downloaded by `root` user in the Dockerfile. But PHP-FPM runs as `www-data` user.

```
Without this:
    Files owned by: root
    PHP-FPM user: www-data
    Result: PHP-FPM can't read files → 403 Forbidden

With this:
    Files owned by: www-data
    PHP-FPM user: www-data
    Result: PHP-FPM can read/write files → Works!
```

---

#### **STEP 4: Start PHP-FPM (Lines 36-38)**

```bash
echo "WordPress: Starting PHP-FPM..."
exec php-fpm -F
```

**What it does:**
- `exec` = Replace current process with PHP-FPM
- `-F` = Run in foreground (required for Docker)

**Why foreground?**

Docker needs the main process to stay in foreground. If it goes to background, Docker thinks container crashed.

```
Wrong: php-fpm          → Goes to background → Docker exits
Correct: php-fpm -F     → Stays in foreground → Docker keeps running
```

---

## **Part 3: What Needs to Be Installed?**

### **In Dockerfile**

```dockerfile
FROM alpine:latest

RUN apk update && apk add --no-cache \
    php-fpm \
    php-mysqli \
    php-json \
    php-curl \
    php-dom \
    php-gd \
    php-mbstring \
    php-opcache \
    php-zip \
    wget \
    netcat-openbsd
```

**What each package does:**

| Package | What | Why |
|---------|------|-----|
| **php-fpm** | PHP FastCGI Process Manager | Runs PHP code |
| **php-mysqli** | MySQL/MariaDB library | Connect to database |
| **php-json** | JSON handling | WordPress uses JSON |
| **php-curl** | HTTP client | WordPress needs it |
| **php-dom** | XML/HTML parsing | WordPress plugins use it |
| **php-gd** | Image processing | Image manipulation |
| **php-mbstring** | Multi-byte strings | Unicode support |
| **php-opcache** | PHP bytecode cache | Performance |
| **php-zip** | ZIP file support | Plugin/theme uploads |
| **wget** | Download tool | Fetch WordPress from internet |
| **netcat-openbsd** | Network testing | Check port availability |

**What happens:**
1. Alpine Linux boots up (tiny OS, ~5MB)
2. Install PHP and extensions (~100MB)
3. Create `/var/www/html` directory
4. Copy configuration files
5. Set entrypoint script

---

## **Part 4: Does It Depend on Volumes?**

### **Short Answer: SORT OF**

WordPress runs **without volumes**, but data is **lost when container stops**.

---

### **Scenario A: WITHOUT Volume**

```
Container starts
    ↓
entrypoint.sh downloads WordPress (~100MB)
    ↓
WordPress installed in container
    ↓
Container stops/restarts
    ↓
All data DELETED
    ↓
Next startup: Re-downloads WordPress (slow)
```

**Problems:**
- Lost posts, comments, settings
- Slow restarts (re-downloads each time)
- Can't see WordPress on your computer

---

### **Scenario B: WITH Volume (What we use)**

```
Your Computer:              Container:
~/data/wordpress     ←→     /var/www/html
    ↓
    Shared folder
```

**What happens:**

```
First Start:
    Container starts
        ↓
    entrypoint.sh downloads WordPress
        ↓
    Saved to /var/www/html
        ↓
    Volume syncs it to ~/data/wordpress
        ↓
    Container stops

Second Start:
    Container starts
        ↓
    entrypoint.sh checks: Does wp-load.php exist?
        ↓
    YES (from volume) → Skip download
        ↓
    WordPress ready in milliseconds
        ↓
    You can see files in ~/data/wordpress
```

**Benefits:**
- ✅ Persistent data (survives restarts)
- ✅ Fast restarts (no re-download)
- ✅ See files on computer
- ✅ Edit files directly

---

### **Volumes in docker-compose.yml**

```yaml
volumes:
  wp:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/${USER}/data/wordpress

services:
  wordpress:
    volumes:
      - wp:/var/www/html
```

**Translation:**

```
WordPress service:
    Mount volume "wp" to /var/www/html

Volume "wp":
    Type: bind mount
    Host path: /home/pettop/data/wordpress
    Container path: /var/www/html
```

**Bind Mount = Shared Folder**

```
/home/pettop/data/wordpress (your computer)
    ↓ Same folder ↓
/var/www/html (inside container)
```

Any changes in one = reflected in other!

---

## **Part 5: What is an Image?**

### **Image = Blueprint/Recipe**

Think of Docker Image like a recipe:

```
Recipe (Image):
├── Start with: Alpine Linux
├── Add: PHP packages
├── Add: WordPress download logic
├── Configuration: php-fpm.conf
├── Entrypoint: entrypoint.sh
└── Instructions: Run this when starting

Container = Cooking the Recipe
    When you run the recipe
    You get a running WordPress container
```

---

### **Image vs Container**

| Aspect | Image | Container |
|--------|-------|-----------|
| **What** | Blueprint/template | Running instance |
| **File** | Dockerfile (text) | Process (running code) |
| **Stored** | On disk | In RAM + disk |
| **Can edit** | Edit Dockerfile | Can't edit running container |
| **Create** | `docker build` | `docker run` / `docker-compose up` |
| **Multiple** | 1 image | Multiple containers from 1 image |
| **Persistent** | Yes | No (data lost unless volume) |

---

### **Image Layers**

Dockerfile is built in layers:

```dockerfile
FROM alpine:latest
     ↓ Layer 1: Alpine OS

RUN apk add php-fpm
     ↓ Layer 2: PHP-FPM added

RUN apk add wget
     ↓ Layer 3: wget added

COPY ./conf/php-fpm.conf ...
     ↓ Layer 4: Config file

COPY ./tools/entrypoint.sh ...
     ↓ Layer 5: Entrypoint script

EXPOSE 9000
     ↓ Layer 6: Port exposed
```

**Each layer builds on previous:**

```
Layer 6 (top) ← EXPOSE
     ↓
Layer 5       ← entrypoint.sh
     ↓
Layer 4       ← php-fpm.conf
     ↓
Layer 3       ← wget
     ↓
Layer 2       ← php-fpm
     ↓
Layer 1       ← Alpine OS (base)
```

---

## **Part 6: Complete Workflow Tutorial**

### **Step 1: Docker Builds Image**

```bash
make
```

**What happens:**

```
Docker reads: Dockerfile
    ↓
Build Layer 1: Alpine Linux (~5MB)
    ↓
Build Layer 2: Install PHP packages (~100MB)
    ↓
Build Layer 3: Create directories
    ↓
Build Layer 4: Copy configuration files
    ↓
Build Layer 5: Copy entrypoint.sh
    ↓
Final Image: wordpress (~150MB)
    ↓
Image stored on disk
    ↓
Ready to create containers
```

---

### **Step 2: Container Starts from Image**

```bash
docker-compose up
```

**What happens:**

```
Docker sees: "Create wordpress container from wordpress image"
    ↓
Load Image from disk
    ↓
Create fresh container instance
    ↓
Mount volume: ~/data/wordpress → /var/www/html
    ↓
Run entrypoint.sh
```

---

### **Step 3: Entrypoint Script Runs**

```bash
# Inside container boot
entrypoint.sh starts
    ↓
STEP 1: Wait for MariaDB
    Check port 3306 every 1 second
    MariaDB comes online → Continue
    ↓
STEP 2: Install WordPress
    Check if wp-load.php exists?
    First run: NO → Download & install
    Later runs: YES → Skip (use volume)
    ↓
STEP 3: Fix permissions
    chown -R www-data /var/www/html
    All files now readable by PHP-FPM
    ↓
STEP 4: Start PHP-FPM
    exec php-fpm -F
    Container ready!
```

---

### **Step 4: Data Flow**

```
Browser Request on port 443
    ↓
Nginx receives request
    ↓
Nginx → PHP-FPM (FastCGI) on port 9000
    ↓
PHP-FPM reads WordPress files from /var/www/html
    ↓
Mounted volume: /var/www/html ← → ~/data/wordpress
    ↓
PHP executes WordPress code
    ↓
WordPress queries MariaDB on port 3306
    ↓
Response back to Browser
```

---

### **Step 5: Container Stops**

```bash
make down
```

```
User sends: docker-compose down
    ↓
Docker sends SIGTERM signal to PHP-FPM
    ↓
PHP-FPM gracefully exits
    ↓
Container stops
    ↓
Container removed
    ↓
Files in /var/www/html DELETED from container
    ↓
BUT: Volume saved everything to ~/data/wordpress
    ↓
Data is safe!
```

---

### **Step 6: Container Restarts**

```bash
make
```

```
New container created from image
    ↓
Volume mounts: ~/data/wordpress → /var/www/html
    ↓
entrypoint.sh starts
    ↓
STEP 2: Check wp-load.php
    File exists (from volume)
    SKIP download
    ↓
WordPress ready immediately!
    ↓
PHP-FPM starts
    ↓
Browser shows: Same WordPress site!
    All posts, settings, users intact!
```

---

## **Part 7: Image Sizes**

```
Alpine Base:           ~5MB
PHP packages:         ~100MB
Downloaded WordPress:  ~20MB (not in image, in volume)
Total Image:          ~125MB
```

**Per Container Instance:**

```
Image reused:          0MB (shared)
Container filesystem:  ~100MB
WordPress files:       ~20MB (in volume)
Total per container:   ~120MB RAM (running)
```

---

## **Part 8: Container Lifecycle Diagram**

```
┌─────────────────────────────────────────────────────────┐
│                   DOCKERFILE                            │
│  FROM alpine → RUN packages → COPY config → ENTRYPOINT  │
└──────────────────┬──────────────────────────────────────┘
                   │ docker build
                   ▼
┌─────────────────────────────────────────────────────────┐
│                   IMAGE                                  │
│    Blueprint ready to use (stored on disk)              │
└──────────────────┬──────────────────────────────────────┘
                   │ docker run / docker-compose up
                   ▼
┌─────────────────────────────────────────────────────────┐
│                  CONTAINER (Running)                     │
│                                                          │
│  1. entrypoint.sh starts                                │
│  2. Wait for MariaDB                                    │
│  3. Install/Check WordPress                            │
│  4. Fix permissions                                    │
│  5. Start PHP-FPM                                      │
│  6. Ready to serve requests                            │
└──────────────────┬──────────────────────────────────────┘
                   │ docker stop / docker-compose down
                   ▼
┌─────────────────────────────────────────────────────────┐
│                 CONTAINER (Stopped)                      │
│  - Container removed                                    │
│  - Filesystem deleted                                   │
│  - DATA SAFE in Volume (~/data/wordpress)              │
└─────────────────────────────────────────────────────────┘
```

---

## **Part 9: Common Questions**

### **Q: What if I delete the container?**

```
Answer: 
- Container deleted
- Files in container deleted
- Volume data INTACT
- Can restart and recover everything
```

---

### **Q: What if I modify WordPress files?**

```
Answer:
- Edit ~/data/wordpress/wp-content/themes/style.css
- Changes sync to /var/www/html in container
- Website shows changes immediately
- Changes persist in volume
```

---

### **Q: What if entrypoint.sh fails?**

```
Answer:
- Container doesn't start
- Check logs: docker-compose logs wordpress
- Fix issue in entrypoint.sh
- Rebuild: make fclean and make
```

---

### **Q: Do I need to install WordPress manually?**

```
Answer: NO!
- entrypoint.sh does it automatically
- Just run: make
- WordPress auto-downloads and installs
```

---

### **Q: Why `exec php-fpm`?**

```
Answer:
- exec replaces this process with PHP-FPM
- Docker monitors the foreground process
- If PHP-FPM dies, container exits
- Docker can restart if container died
- Clean shutdown signal handling
```

---

## **Summary**

| What | Details |
|------|---------|
| **entrypoint.sh** | Runs at container boot, sets up WordPress |
| **Step 1** | Wait for database |
| **Step 2** | Download/verify WordPress |
| **Step 3** | Fix file permissions |
| **Step 4** | Start PHP-FPM foreground |
| **Image** | Blueprint made from Dockerfile |
| **Container** | Running instance of image |
| **Volume** | Persistent storage on your computer |
| **First run** | Downloads WordPress (~30 seconds) |
| **Later runs** | Reuses volume (~2 seconds) |
| **Stop** | Removes container, keeps volume data |

🎯 **entrypoint.sh = Container initialization script that sets up WordPress automatically!**
