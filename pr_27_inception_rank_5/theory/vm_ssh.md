Run this command on your school machine (not in the VM):
ssh-keygen -f "/home/pekatsar/.ssh/known_hosts" -R "[localhost]:2222"

Try connecting again:
ssh -p 2222 pekatsar@localhost

curl -kv https://pekatsar.42.fr:8443