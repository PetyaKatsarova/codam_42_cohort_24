!!! for me, Tim's C project: https://github.com/buddhaman/MijnAmbacht/blob/master/src/camera.c

he netinst CD here is a small CD image that contains just the core Debian installer code and a small core set of text-mode programs (known as "standard" in Debian).
The netinst CD here is a small CD image that contains just the core Debian installer code and a small core set of text-mode programs (known as "standard" in Debian).
==============================
f0r3s17% lsb_release -a

No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 22.04.4 LTS
Release:	22.04
Codename:	jammy
========================================
To launch VirtualBox from the terminal, simply type: virtualbox


!! To increase screen size from 'Machine' chose scale 

#### SU & Sudo
    sudo apt update

        This command prompts you for your own password (not the root password), and then it executes the given command (apt update) as the root user.

Granular Control: sudo is often preferred because it can be configured to give limited privileges to specific users for specific commands, which makes it more secure.

    The file /etc/sudoers controls which users can use sudo and which commands they are allowed to run.

Permissions: Requires that the user be part of the sudo group (or is listed in /etc/sudoers).
Feature            | su                           | sudo
-------------------|------------------------------|------------------------------
Usage              | Switch to another user       | Run a single command as another user
Password Required  | Root user password           | Your own user password
Session Behavior   | Logs you in as root/user     | Runs only the specified command as root
Granular Control   | No, full root access         | Yes, controlled via /etc/sudoers
Security           | Less secure (root password shared) | More secure (limited privileges)
=====================================================================
##### CONFIG SUDO:
TTY mode for sudo is enabled through the requiretty option in the /etc/sudoers file. Here's what it means:
requiretty Option:

    Definition: The requiretty setting in the /etc/sudoers file forces sudo to be run from a TTY (teletype), which is an interactive shell or terminal session.
    Purpose: This improves security by ensuring that sudo commands can only be executed by users directly interacting with a terminal.
===================================================================================
##### CRON
Cron is a time-based job scheduler in Unix-like operating systems, such as Linux. It allows you to automatically schedule scripts or commands to run at specific intervals (e.g., daily, weekly, at a certain hour, etc.).

Here's how you can use cron to schedule and interrupt a script:
What Is Cron?

    Purpose: Cron runs scripts and commands automatically at scheduled times. This is useful for tasks like backups, system maintenance, and other repetitive tasks.
    How It Works: You define cron jobs in a file called crontab (short for "cron table"). Each cron job is defined with a specific schedule using a format that specifies minutes, hours, days, months, and weekdays.
    `crontab -e` To schedule a script to run, add a line in the following format: * * * * * /path/to/your/script.sh
    The five * characters represent the schedule, specifying minute, hour, day of month, month, and day of week. For example:

    30 2 * * * /path/to/your/script.sh will run the script every day at 2:30 AM.
    */5 * * * * /path/to/your/script.sh will run the script every 5 minutes.
