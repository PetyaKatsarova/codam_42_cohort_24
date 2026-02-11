The Hosts File - Complete Tutorial
What Is It?
The hosts file is a simple text file on your computer that maps domain names to IP addresses. It's like a local, personal DNS server that your computer checks before asking the internet for a domain's IP address.
How It Works
When you type pekatsar.42.fr in your browser:

First: Your computer checks the hosts file

If it finds pekatsar.42.fr → uses the IP you specified


Second: If not found in hosts file → asks DNS servers on the internet

DNS returns the real IP address



Common Uses

Local development: Make myproject.local point to 127.0.0.1
Testing: Test a website before DNS is set up
Blocking sites: Map unwanted sites to 0.0.0.0 (blocks them)
Your case: Make pekatsar.42.fr point to your local VM

File Location
Linux (Ubuntu, Debian, etc.):
/etc/hosts

Windows:
C:\Windows\System32\drivers\etc\hosts


 Edit with nano (easier) or vim:
 **Step 4:** Add your line at the end:
```
127.0.0.1       pekatsar.42.fr

Solution: SSH Tunnel (Port Forwarding via SSH)
Instead of relying on VirtualBox port forwarding, use SSH to forward the port:
Step 1: SSH into VM with local port forwarding:
ssh -L 8443:localhost:443 -p 2222 pekatsar@localhost
```

This creates a tunnel: `your_laptop:8443` → `VM:443`

**Step 2:** Keep that SSH session open (minimized is fine)

**Step 3:** In browser on your laptop:
```
https://localhost:8443

-------------
ls -la /etc/hosts