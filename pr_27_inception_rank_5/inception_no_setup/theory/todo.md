Option 1: Browser on Host (Recommended for Simplicity)
Create your VM (Debian/Ubuntu) without a GUI.
Set up your web services (WordPress, adminer, etc.) in the VM.
Configure port forwarding or use bridged networking so your host can access the VM’s web server.
On your host machine, open your browser and go to http://localhost:PORT or http://VM_IP:PORT.
You do NOT need a browser inside the VM for most Inception 42 requirements.

Option 2: Browser Inside the VM (with GUI)
Create a new VM and choose a Debian/Ubuntu ISO with a desktop environment (e.g., GNOME, XFCE).
During installation, select a desktop environment (not “server only”).
After installation, log in to the graphical desktop.
Open a terminal and install a browser:
For Firefox:
sudo apt update && sudo apt install firefox-esr
For Chromium:
sudo apt update && sudo apt install chromium
Launch the browser from the applications menu.
Which Should You Use?
If you only need to test web services, use your host’s browser and set up networking accordingly.
If you want to practice with a full desktop in the VM, install a GUI and browser inside the VM.

docker exec -it nginx bash
wget --no-verbose --tries=1 --spider https://localhost:443 --no-check-certificate