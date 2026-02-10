!!NB!!

Nginx is listening on 0.0.0.0:443 (IPv4)
wget is trying to connect to [::1]:443 (IPv6 localhost)

docker port nginx
443/tcp -> 0.0.0.0:443
443/tcp -> [::]:443


// in local machine terminal
 curl -k https://localhost -v


With the VM running, run this command on your laptop:
 VBoxManage showvminfo unstoppable | grep -i forward

 Let's add the port forwarding rule via command line to make sure it works.
First, check which network adapter your VM is using:
VBoxManage showvminfo unstoppable | grep NIC

VBoxManage controlvm unstoppable poweroff
VBoxManage startvm unstoppable --type headless
curl -k https://localhost -v


//Still connection refused. Let's check if something on your laptop is already using port 443.
Next step:
Check what's listening on port 443 on your laptop:
sudo ss -tlnp | grep :443

//Let's verify the VM is actually running and check if Docker containers are up inside it.
ssh -p 2222 pekatsar@localhost

curl -k https://localhost -v

The problem: VirtualBox port forwarding isn't working from your laptop to the VM.
Exit the VM (type exit), then on your laptop run:
VBoxManage controlvm unstoppable natpf1 delete https
VBoxManage controlvm unstoppable natpf1 "https,tcp,127.0.0.1,443,,443"
curl -k https://localhost -v

Still connection refused. This is a known VirtualBox issue on some systems where NAT port forwarding to privileged ports (< 1024) doesn't work without elevated permissions.
Solution: Use a non-privileged port on your laptop.
Next step:
Change the port forwarding to use port 8443 on your laptop (host) instead of 443:
VBoxManage controlvm unstoppable natpf1 delete https
VBoxManage controlvm unstoppable natpf1 "https,tcp,127.0.0.1,8443,,443"