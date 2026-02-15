1. start vm

2. in terminal: (cp files from host to vm)
scp -P 2222 -r inception pekatsar@localhost:/home/pekatsar

3. in terminal
ssh -p 2222 pekatsar@localhost

to run the app:
1. make setup
2. newgrp docker
3. make up
4. Access the app at https://localhost

