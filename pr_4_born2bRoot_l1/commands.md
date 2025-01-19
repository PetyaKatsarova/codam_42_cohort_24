cd 'VirtualBox VMs'

shasum born2bRoot.vdi:
84994e99f892f11504feb9a549a8dfafebba9aaa  born2bRoot.vdi

`sudo apparmor_status` check if appArmor works: security sys provides mandatory access control(mac)

#### 1. lsblk
`head -n 2 /etc/os-release`

2. `su` - //login in as the root user.

The -y flag in apt-get update -y stands for "yes". It automatically answers "yes" to any prompts that may come up during the execution of the command.

#### 3. Add user to sudo group
`usermod -aG sudo pekatsar`
`getent group sudo` // to check who's in the sudo gr
//The usermod command in Linux is used to modify a user's account settings. It's a powerful command that allows administrators to make various changes to user properties, including group memberships, login names, home directories, and more. //

for nano: CONTROL+O to save, CTRL+X to exit

#### 4. OpenSSH-Server
 is software that allows you to connect to a computer remotely using the SSH (Secure Shell) protocol. It provides secure encrypted communication over an insecure network, allowing users to manage servers, transfer files, or execute commands remotely.

`sudo systemctl status ssh` // check SSH Server Status
`sudo grep Port /etc/ssh/sshd_config` //check if the port settings are right 4242
sudo service ssh restart`OpenSSH-Server is software that allows you to connect to a computer remotely using the SSH (Secure Shell) protocol. It provides secure encrypted communication over an insecure network, allowing users to manage servers, transfer files, or execute commands remotely.

!! APT-GET package to download packages

#### 5. UFW
`sudo ufw enable`
`sudo ufw status numbered` //check the status of UFW and allowed ports
`sudo ufw allow 8080`
`sudo ufw delete allow 8080`

#### 6. SSH connection:
in machine terminal: `ssh pekatsar@127.0.0.1 -p 4242`
`exit`
root should not be able to ssh: 
`sudo nano /etc/ssh/sshd_config` `PermitRootLogin no`

#### 7. PWD policy
a. in `sudo nano /etc/pam.d/common-password` add minlen, u, lower case -1 means: at least one,difok=7 min 7 diff chars from prev pwd
b. `sudo vim /etc/login.defs` `PASS_MAX_DAYS 30` and `PASS_MIN_DAYS 2` keep `PASS_WARN_AGE 7`

#### 8. Creating a group:
sudo groupadd user42
sudo groupadd evaluating
getent group // check group created

#### 9. Creating usr and assing him to a group
`cut -d: -f1 /etc/passwd` // check all local usrs
`sudo adduser new_username`
`sudo usermod -aG user42 username`
`sudo usermod -aG evaluating username`
`getent group user42`
`getent group evaluation`
`groups`
`chage -l username` checks if pwd rules working in users
`groups username` checks all groups user is in
`sudo gpasswd -d usr_name groupname` rmv user from a gr

#### 10. Creating sudo.log
`cd ~/../../var/log/sudo`
`sudo nano sudo.log`

#### 11. Config sudoers group
`sudo nano /etc/sudoers` to go the sudoers file
The goal of editing this file is to apply specific behaviors and restrictions when using sudo.
```
Defaults	env_reset
Defaults	mail_badpass
Defaults	secure_path="/usr/local/sbin:/usr/local/bin:/usr/bin:/sbin:/bin"
Defaults	badpass_message="Password is wrong, please try again!"
Defaults	passwd_tries=3
Defaults	logfile="/var/log/sudo/sudo.log"
Defaults	log_input, log_output
Defaults	requiretty
```

#### 12. Crontab Config And Interrupt
- `cd /usr/local/bin` – to show monitoring.sh
- `sudo crontab -u root -e` – to edit the cron job
- `change script to */1 * * * * sleep 30s && script path` – to run it every 30 seconds, delete the line to stop the job from running.

Type `sudo crontab -u root -e` to open the crontab and add the rule at the end of the crontab: `*/10 * * * * /usr/local/bin/monitoring.sh` this means that every 10 mins, this script will show
interupt:
a. find process id; `ps aux | grep script.sh` after ur usern is pid
`kill <pid>` if not stopping `kill -9 <pid>`
`sudo systemctl stop cron`
the crontab allows you to schedule a script to run automatically at a certain time or interval.
Interrupting the Script: To interrupt the running script, you use process management commands like ps to find the PID and kill to terminate it.

`date`
`timedatectl` shows more info

### 13. Evaluation Commands for UFW, Group, Host, lsblk and SSH

- `sudo ufw status`
- `sudo systemctl status ssh`
- `getent group sudo`
- `getent group user42`
- `sudo adduser new username`
- `sudo groupadd groupname`
- `sudo usermod -aG groupname username`
- `sudo chage -l username` - check password expire rules
- `hostnamectl`
- `hostnamectl set-hostname new_hostname` - to change the current hostname
- Restart your Virtual Machine.
- `sudo nano /etc/hosts` - change current hostname to new hostname
- `lsblk` to display the partitions
- `dpkg -l | grep sudo –` to show that sudo is installedd 
- `sudo ufw status numbered`
- `sudo ufw allow port-id`
- `sudo ufw delete rule number`
 