docker ps -a   
docker stop nginx wordpress mariadb   
docker rm nginx wordpress mariadb     

or:
docker rm -f $(docker ps -aq)

rmv all unused volumes:
docker volume prune

docker volume rm srcs_db srcs_wp

ssh -p 2222 pekatsar@localhost

hostname

sudo hostnamectl set-hostname inception

sudo nano /etc/hostname

sudo nano /etc/hosts
```
Change the line with 127.0.1.1 from old hostname to new:
```
127.0.1.1    inception

scp -P 2222 -r inception_no_setup/ pekatsar@localhost:~/

docker logs wordpress

VBoxManage controlvm unstoppable natpf1 "https,tcp,127.0.0.1,8443,,443"
// unstoppable is the name of the machine

// secrets:
cd ~/inception_no_setup && mkdir -p secrets && echo "wordpress_password_123" > secrets/db_password.txt && echo "root_password_456" > secrets/db_root_password.txt && ls -la secrets/

cd ~/inception_no_setup && mkdir -p secrets && echo "wordpress_password_123" > secrets/db_password.txt && echo "root_password_456" > secrets/db_root_password.txt && echo "admin_password_123" > secrets/wp_admin_password.txt && echo "user_password_456" > secrets/wp_user_password.txt && ls -la secrets/

https://localhost:8443/
https://localhost:8443/wp-admin/


// text-based browser
sudo apt update && sudo apt install lynx

Open your terminal.
Type: lynx example.com (replace example.com with your target site).
Use the arrow keys to navigate.
Press Q to quit, Y to confirm exit.
Basic navigation in lynx:
Up/Down arrows: Move between links.
Right arrow/Enter: Follow a link.
Left arrow: Go back.
G: Go to a new URL.
/: Search for text on the page.

lynx https://localhost
// got certificate is not trusted

docker logs nginx
