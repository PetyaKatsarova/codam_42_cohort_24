
display wp webapp on local machine, which runs on 3 dockers files in the vm:

1. in vm: 
ip a
// look for the inet address on your main interface (often eth0 or ens33). That IP is the VM’s address.

lo: loopback (local-only) 127.0.0.1.
enp0s3: your VM’s main network card. The IPv4 inet 10.0.2.15/24 is the VM’s IP (NAT range). Use this to access services from the host if networking/port‑forwarding allows it.
docker0: Docker’s default bridge on the VM (172.17.0.1), internal to Docker.
br-... and veth...: Docker bridge and virtual Ethernet pairs for containers.
So the VM IP is 10.0.2.15 on enp0s3.

2. in local machine browser:
scp -P 2222 -r /path/to/inception pekatsar@localhost:/home/pekatsar/

3. to list all docker volumes:
docker volume ls

4. need to add rules in vm/settings/network/port forwarding
....

5. in local machine browser run:
localhost:yourhost port
localhost:8443