git clone repo_name

1. need to set up all permissions run:
./setup.sh

2. need to create secrets, run:
./create_secrets.sh

3. rename .env.example to .env and fill in your values

4. ready to go, just type:
make

4.5 access the website: default nginx port is 443, that's why use is optional
https://localhost:443/
https://localhost/wp-admin/

5. make clean will rm containers, volumes stay

6. make fclean will rm containers and volumes

