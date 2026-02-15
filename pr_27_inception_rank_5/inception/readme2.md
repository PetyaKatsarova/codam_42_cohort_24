**first time setup instructions**
run in wsl or linux terminal on host machine:
setup2.sh

if in wsl
# Open Command Prompt as Administrator, then:
notepad C:\Windows\System32\drivers\etc\hosts
there add: 127.0.0.1 pekatsar.42.fr

**to run the app:**

1. start vm

2. in wsl/linux host terminal: (cp files from host to vm)
scp -P 2222 -r inception pekatsar@localhost:/home/pekatsar

3. if you would like to access vm from host terminal
ssh -p 2222 pekatsar@localhost





