Run this command on your school machine (not in the VM):
ssh-keygen -f "/home/pekatsar/.ssh/known_hosts" -R "[localhost]:2222"

Try connecting again:
ssh -p 2222 pekatsar@localhost

curl -kv https://pekatsar.42.fr:8443

ip addr show

**debug vm set up for local machine website display**
docker exec nginx netstat -tlnp | grep 443

curl -k https://localhost:8443 -v

sudo ss -tlnp | grep 8443

docker port nginx