

1. hostname

sudo hostnamectl set-hostname pekatsar
sudo nano /etc/hostname
Replace the content with your new hostname (just one word, like pekatsar), save and exit.

Step 5: Also update /etc/hosts:
bashsudo nano /etc/hosts
```

Find the line with `127.0.1.1` and change the old hostname to the new one:
```
127.0.1.1    pekatsar

in vm sudo nano /etc/hosts:

```
127.0.0.1       localhost
127.0.1.1       pekatsar2

# The following lines are desirable for IPv6 capable hosts
::1     localhost ip6-localhost ip6-loopback
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters

# Inception project
127.0.0.1       pekatsar.42.fr
```

No restart needed!
Changes to /etc/hosts take effect immediately.

Inside VM: curl https://pekatsar.42.fr works
Laptop browser: https://pekatsar.42.fr:8443 still won't work (needs laptop's /etc/hosts)
Laptop browser: https://localhost:8443 works
===============================

1. cd ~/inception
grep -r "^FROM" srcs/               // alpine
Check running containers (shows actual OS inside):
docker exec nginx cat /etc/os-release
docker exec wordpress cat /etc/os-release
docker exec mariadb cat /etc/os-release