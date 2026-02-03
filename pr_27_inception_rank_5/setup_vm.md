https://www.notion.so/Inception-2507bc29ae7180108447dbde19ddf6be

1. I use Oracle VirtualBox
(sudo apt update
sudo apt install virtualbox)
2. download debian 13 trixie latest stable netinst ISO
3. create new virtual machine

.ISO File (Image of Optical Disc)
What it is: A copy of installation CD/DVD
Purpose: Used to install an operating system
Like: A Windows/Debian installation USB stick
Use case: You boot from it and go through installation wizard
Can't modify: Read-only, it's just the installer
Example: debian-12.5.0-amd64-netinst.iso
.VDI File (Virtual Disk Image)
What it is: A virtual hard drive
Purpose: The actual installed operating system lives here
Like: Your computer's hard drive/SSDhttps://www.notion.so/Inception-2507bc29ae7180108447dbde19ddf6be
Use case: This IS your VM's storage (OS + your files)
Can modify: Reads/writes data, saves your changes
Example: Debian_Inception.vdi
---------------------------------

Base Memory
What: RAM (temporary memory) for the VM
Like: Your computer's RAM sticks
Used for: Running programs, keeping data while VM is on
Lost when: VM shuts down
Set to: 2048 MB (2 GB) for Inception
Hard Disk
What: Storage space (like SSD/HDD) for the VM
Like: Your computer's hard drive
Used for: Installing OS, saving files permanently
Keeps data: Even after VM shuts down
Set to: 30 GB for Inception
Simple:
Base Memory (RAM) = Working memory (temporary)
Hard Disk = Storage (permanent)
You need both! Set:

Base Memory: 2048 MB
Hard Disk: 30 GB
--------------
start the vm:
VM window → View menu → Virtual Screen 1
Try: Scale to 200% or Adjust Window Size
OR

Click View → Scaled Mode (or press Host+C)
Host key = Right Ctrl (usually)
------------------------
system hostname:
pekatsar42

domain name: is blank

real name: Petka Motoretka
username: pekatsar, pwd is ch...


