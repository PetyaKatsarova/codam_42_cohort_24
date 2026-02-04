**.bashrc** is the “bash run commands” file. It’s a shell script that runs every time you start an interactive non‑login Bash shell. It typically contains:

Aliases (e.g., alias ll='ls -la')
Environment variables (e.g., export PATH=...)
Prompt configuration (PS1)
Shell options (shopt, set)
Functions and custom commands
Tool initializations (e.g., nvm, conda)

--------------------------------------------

A **locale** tells programs your language, character encoding, number/date formats, and sorting rules.
It’s used by tools like apt, perl, bash, and editors to format text and handle UTF‑8 correctly.
a warning means some locales you set (e.g., nl_NL.UTF-8) aren’t installed, so Perl falls back.
Fix steps (VM):

Check installed locales:
locale -a
Generate needed locales:
sudo locale-gen en_US.UTF-8
Set defaults:
sudo update-locale LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8
Log out/in (or reboot).

debug:
grep -R "LC_" ~/.bashrc ~/.profile ~/.bash_profile /etc/default/locale /etc/environment

unset LC_ALL LC_CTYPE LC_NUMERIC LC_TIME LC_MESSAGES LC_MONETARY LC_ADDRESS LC_IDENTIFICATION LC_MEASUREMENT LC_PAPER LC_TELEPHONE LC_NAME

sudo update-locale LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8

logout ssh and login again, check:
locale

---------------------------------------------------
drwxrwxr-x 3 wil wil 4096 avril 42 20:42 
4096 = size in bytes (directory entries; directories often show 4096).
avril 42 20:42 = last modified date/time (April 42 is just the locale’s date format; “42” is the day).
3 right after permissions = number of hard links to that directory.


--------------------------------------------------------

Next step: create the project skeleton (Makefile + srcs folder with docker-compose.yml, .env, and requirements/{nginx,wordpress,mariadb,tools}).

todo:
Sensitive files like .env/secrets can be created on the VM and kept out of Git.

---------------------------------------
1. 
mkdir -p srcs/requirements/{nginx,wordpress,mariadb,tools}

-p tells mkdir to create parent directories as needed and not error if they already exist.

2. 
touch Makefile srcs/docker-compose.yml srcs/.env
---------------------------------------------
**ports** maps host ports to container ports using "HOST:CONTAINER".

"443:443" means:
Host port 443 → Container port 443 (NGINX TLS).
Users connect to host 443; Docker forwards to NGINX inside container.
To change the public port (outside):

Use "8443:443" → access via https://yourdomain:8443.
To change the container port (inside):

You must also change NGINX to listen on that port. Example "8443:8443" with NGINX listening on 8443.
Rule of thumb:

Left side = public port on VM.
Right side = port your service listens on inside the container.


