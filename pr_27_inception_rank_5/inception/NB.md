Step-by-step: Add hostname to Windows hosts file

Press Win + R
Type: notepad C:\Windows\System32\drivers\etc\hosts
Click OK
Click "Yes" if admin prompt appears
At the end of the file, add new line:
127.0.0.1 inception.42.fr
Press Ctrl + S (Save)
Close Notepad
Test:
Open browser, go to: https://inception.42.fr

Host vs Guest

The Three Layers
1. [Host = Your Laptop/Physical Machine]
        ↓ VM Port Forwarding
2. [Guest = VM (Ubuntu running in VirtualBox/VMware)]
        ↓ Docker Port Mapping
3. [Container = Docker container running inside the VM]
Breaking It Down:
Layer 1: Host (Your Laptop)

Your physical machine
Where you run VirtualBox/VMware
Where you open the browser
Layer 2: Guest (The VM)

Ubuntu running inside VirtualBox/VMware
Where Docker engine runs
Has its own network interface
Layer 3: Container (Inside VM)

Docker containers (nginx, wordpress, mariadb)
Running inside Docker inside the VM
Each has its own isolated network
Two Separate Port Mappings:
1. VM Port Forwarding (VirtualBox/VMware settings):
Host Port 443 → Guest Port 8443
(Laptop:443)  →  (VM:8443)
2. Docker Port Mapping (in your docker-compose or docker run):
-p 8443:443
(VM:8443)  →  (Container:443)
Complete Flow:
Browser on laptop: https://localhost:443
    ↓ [VM Port Forwarding]
VM listens on: 8443
    ↓ [Docker Port Mapping]
Nginx container listens on: 443
The container is NOT the guest. The VM is the guest. The container lives inside the guest (VM).