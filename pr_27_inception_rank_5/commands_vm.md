su -
apt update
apt install sudo
usermod -aG sudo pekatsar
getent group sudo
exit

su -
echo "pekatsar ALL=(ALL:ALL) ALL" >> /etc/sudoers.d/pekatsar
chmod 440 /etc/sudoers.d/pekatsar
exit

sudo systemctl status ssh
whoami
ip addr show
Look for inet 10.0.2.15 or similar.
inet 10.0.2.15/24

Now set up port forwarding:
sudo poweroff

In VirtualBox Manager:

Select your VM
Settings → Network
Adapter 1 → Advanced (dropdown)
Click Port Forwarding button
Click + icon (top right)
Fill in:
Name: SSH
Protocol: TCP
Host IP: 127.0.0.1
Host Port: 2222
Guest IP: (leave empty)
Guest Port: 22
Click OK → OK
Start VM
From your laptop terminal:
ssh -p 2222 pekatsar@localhost

Click the + icon (insert new rule - top right or side of window)
Fill in the new row:
Name: SSH
Protocol: TCP
Host IP: 127.0.0.1
Host Port: 2222
Guest IP: (leave empty)
Guest Port: 22
Click OK
Click OK again (to close Settings)
Start your VM

from your laptop:
ssh -p 2222 pekatsar@localhost

in vm:
sudo nano /etc/ssh/sshd_config
add:
UseDNS no
Save (Ctrl+O, Enter, Ctrl+X), 


ssh -p 2222 pekatsar@localhostyes