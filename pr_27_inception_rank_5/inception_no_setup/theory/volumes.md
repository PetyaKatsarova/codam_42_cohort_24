Docker volumes are objects managed by Docker. When you inspect a volume, you get a JSON object describing its metadata.
docker volums inspect inception_db

{
    "CreatedAt": "2026-02-12T12:21:32+01:00",
    "Driver": "local",
    "Labels": {
        "com.docker.compose.project": "inception",
        "com.docker.compose.version": "2.23.0",
        "com.docker.compose.volume": "db"
    },
    "Mountpoint": "/var/lib/docker/volumes/inception_db/_data",
    "Name": "inception_db",
    "Options": null,
    "Scope": "local"
}

Driver

The plugin managing the volume storage.
"local" means Docker stores it on the host filesystem, in /var/lib/docker/volumes/....
Other drivers could store data on network storage, cloud, or third-party plugins.

Mountpoint

Physical path on the host where the data lives:
/var/lib/docker/volumes/inception_db/_data
All container data stored in this volume is in this folder.
You generally don't touch it manually, Docker handles it.

Scope

"local" means the volume is stored on this host only.
Other scopes like "global" exist for Swarm, meaning accessible across nodes.

Docker volumes provide persistent storage independent of containers.

Purpose: Containers are ephemeral; if a container is removed, its data should not disappear.

Lifecycle:

Create volume → attach to container → container writes/reads → remove container → data stays → optional docker volume rm to delete.

Isolation:

Each volume is isolated; one container can’t accidentally overwrite another’s volume unless explicitly mounted.

In Compose: Volumes are tied to projects via labels (com.docker.compose.project), which allows multiple projects to have same volume names without conflict.

Mounting: Inside a container, volumes appear as a folder (e.g., /var/lib/mysql) but the underlying data is on host (/var/lib/docker/volumes/.../_data).

inception_db = MariaDB data

Driver: local = safe, Docker-managed

Labels = Compose keeps track

Mountpoint = where Docker physically stores it

Scope = local to your host

--------------------------------------------

in docker-compose.yml:
volumes:
  - db:/var/lib/mysql

db = the Docker volume (logical name)

/var/lib/mysql = the path inside the container where the volume is mounted
MariaDB container sees /var/lib/mysql as a normal folder.

Anything MariaDB writes there is stored in the Docker volume db, not inside the container’s ephemeral filesystem.

Even if you remove the container, the data persists in the volume.

Docker-managed volume (db:/var/lib/mysql)

Docker controls where it physically lives

You cannot see it easily on host without looking in /var/lib/docker/volumes/...

Safer, portable, and avoids path conflicts

Managed by Docker Compose → project-specific labels
eature	Docker volume (db:/var/lib/mysql)	Bind mount (./data/mariadb:/var/lib/mysql)
Location	Docker-managed path	Host path (your folder)
Portability	High	Low (depends on folder existing)
Host access	Hard to access	Easy, direct
Lifecycle	Independent of container	Host folder stays anyway
Use case	DB data, persistent container data	Dev files, logs, local editing

So yes:

The volume is mounted inside MariaDB container at /var/lib/mysql

Physically the data is on your machine, but Docker manages it

If you delete the container, data stays











-----------------------------------------------
DRIVER

Shows the volume plugin Docker uses to store the data.

local = volume stored on your host filesystem (default Docker behavior).
/var/lib/docker/volumes/<volume_name>/_data
This is where all MySQL / WordPress files for your volume are physically stored.

Other drivers exist (for network storage, cloud, etc.), e.g., nfs, azurefile, flocker.
-----
Volume name = logical name (inception_db)

Driver = how/where Docker stores it (local = host filesystem).
-----
No — local is not a bind. They are different.

1️⃣ local volume
volumes:
  inception_db:
    driver: local


Docker manages the data itself.

Stored under Docker’s path, e.g., /var/lib/docker/volumes/inception_db/_data.

You don’t need to know the exact location, Docker handles it.

Safer for portability; works the same on any host.

Bind mount (type: bind)
volumes:
  - ./data/mariadb:/var/lib/mysql


Maps a host folder (./data/mariadb) directly into the container.

Changes on the host immediately reflect in the container and vice versa.

You control the exact folder and can see the files directly.

Often used for development, persistent files you want to inspect.
Feature	local volume	bind mount
Location	Docker-managed	Host folder
Portability	High	Low (path must exist)
Access host FS	Not directly	Direct
Use case	DB data, container data	Dev files, logs, config