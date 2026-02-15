# need to be in root of project to run this script
mkdir -p secrets
chmod 700 secrets

# Generate strong passwords
openssl rand -base64 32 > secrets/db_password.txt
openssl rand -base64 32 > secrets/db_root_password.txt
openssl rand -base64 32 > secrets/wp_admin_password.txt
openssl rand -base64 32 > secrets/wp_user_password.txt

# Set restrictive permissions
chmod 600 secrets/*.txt
ls -la secrets/
