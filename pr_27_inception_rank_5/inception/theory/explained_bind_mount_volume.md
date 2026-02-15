** Bind Mount **
HOST MACHINE                    CONTAINER
============                    =========

/home/user/data/mariadb  ←→  /var/lib/mysql
(You specify exact path)     (Container path)

Direct link - same files, real-time sync


Named Volume
HOST MACHINE                              CONTAINER
============                              =========

/var/lib/docker/volumes/db/_data  ←→  /var/lib/mysql
(Docker manages this path)            (Container path)

Docker controls where data lives

You control host path
Direct filesystem link
Changes on host → instant in container
Changes in container → instant on host
Same physical files (not copied)

example: # On host
echo "test" > /home/user/data/mariadb/test.txt

# In container (instantly available)
docker exec mariadb cat /var/lib/mysql/test.txt
# Shows: test

---------------------

Named Volume
Docker chooses where data lives

Docker controls host path
Data managed by Docker
Portable between machines
Survives container deletion
Better performance (Docker-optimized)


!!NB!!
Both bind mounts and volumes create a direct link, not a copy.

--------------------------------
Convert Bind Mounts to Named Volumes - Tutorial
Understanding the Requirement
Subject says:

Use Docker named volumes (not bind mounts)
Store data in /home/

Problem: These two requirements seem contradictory!
Let me show you both interpretations:

volumes:
  db:
    driver: local
    driver_opts:
      type: none
      o: bind                              # ← Bind mount
      device: /home/${USER}/data/mariadb   # ← You specify path
-------------------------------

volumes:
  db:
    driver: local
  wp:
    driver: local
```

**Where data is stored:**
```
/var/lib/docker/volumes/inception_db/_data
/var/lib/docker/volumes/inception_wp/_data

NOT in /home/ - This contradicts the subject!
-------------------------------

Interpretation 2: Named Volumes with Custom Mountpoint
This satisfies BOTH requirements: named volumes + /home/ storage.

"Named volumes" means volumes defined in the volumes: section with a name.
volumes:
  db:      # ← This IS a named volume
  wp:      # ← This IS a named volume

"Bind mounts not allowed" likely means: Don't use -v /host/path:/container/path in docker run.

# Check where data is stored
docker volume inspect inception_db

# Should show:
# "Mountpoint": "/home/username/data/mariadb"

# Verify data exists
ls -la /home/${USER}/data/mariadb
ls -la /home/${USER}/data/wordpress
-------------------------------- 

Subject says "store in /home/" - pure named volumes can't do this
Your volumes ARE named (db, wp)
They're in the volumes: section (not inline)
This is the only way to satisfy BOTH requirements

Alternatively, ask evaluator to clarify which requirement to ignore:

Named volumes? (then use bind mounts)
/home/ storage? (then use pure named volumes in /var/lib/docker)

You cannot satisfy both with pure Docker - this is why your current setup exists.