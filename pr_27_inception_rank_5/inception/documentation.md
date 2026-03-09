
This is a initial set up of an app which consists of 3 docker containers (mariadb, wordpress, nginx) and 2 volumes for db and wordpress. We will run it in a vm (or remote server).

// in case u want to run it in windows using wsl:
# Open Command Prompt as Administrator, then:
notepad C:\Windows\System32\drivers\etc\hosts
there add: 127.0.0.1 pekatsar.42.fr

**to run the app:**

1. start vm
to open browser:
startx /usr/bin/chromium

2. Only first time using the vm for this app run:
./setup.sh

3. run create_secrets.sh or set it up yourself

4. create .env file based on the .env.template and fill in your data

5. in wsl/linux host terminal: (cp files from host to vm)
scp -P 2222 -r inception pekatsar@localhost:/home/pekatsar

6. if you would like to access vm from host terminal
ssh -p 2222 pekatsar@localhost

7. if you would like to use as root for docker /home/pekatsar/data as per subject requirements for the volumes: not bind, named but in that dir: follow volumes_path_set.sh: u run commands in terminal, not the script.

7.1 in the vm, have installed min browser:

8. debug:
	a.) if your vm runs out of space:
	df -h
	disk free, -h human readable

	du -h --max-depth=1 /

	sudo du -h --max-depth=1 /var
sudo du -h --max-depth=1 /usr
sudo du -h --max-depth=1 /var

/var: "Variable" data—files that change often, like logs, caches, mail, databases, and application data.

/var/lib: Application state data, especially for services and package managers. For Docker, this is where images, containers, and volumes are stored. It is normal for /var/lib to be the fullest if you use Docker or databases.

/var/log: System and application logs.

/var/cache: Cached files for package managers and applications.

/usr: User programs and data—binaries, libraries, documentation, and shared files.

/usr/bin: Most user commands and executables.

/usr/lib: Libraries for programs in /usr/bin and /usr/sbin.

/usr/share: Architecture-independent data (docs, icons, etc.).
-------------------------------------

docker system prune -a --volumes
sudo rm -rf /var/log/*
sudo rm -rf /var/cache/*
sudo rm -rf /tmp/*
sudo rm -rf /var/tmp/*






