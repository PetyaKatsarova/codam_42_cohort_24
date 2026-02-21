
This is a initial set up of an app which consists of 3 docker containers (mariadb, wordpress, nginx) and 2 volumes for db and wordpress. We will run it in a vm (or remote server).

// in case u want to run it in windows using wsl:
# Open Command Prompt as Administrator, then:
notepad C:\Windows\System32\drivers\etc\hosts
there add: 127.0.0.1 pekatsar.42.fr

**to run the app:**

1. start vm

2. Only first time using the vm for this app run:
./setup.sh

3. run create_secrets.sh or set it up yourself

4. create .env file based on the .env.template and fill in your data

5. in wsl/linux host terminal: (cp files from host to vm)
scp -P 2222 -r inception pekatsar@localhost:/home/pekatsar

6. if you would like to access vm from host terminal
ssh -p 2222 pekatsar@localhost

7. if you would like to use as root for docker /home/pekatsar/data as per subject requirements for the volumes: not bind, named but in that dir: follow volumes_path_set.sh: u run commands in terminal, not the script.





