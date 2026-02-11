Here’s the difference and reasoning:

Docker secrets (Swarm mode):
Secrets are managed securely by Docker, stored encrypted, and only exposed to containers at runtime.
They appear at /run/secrets inside the container.
Only available in Docker Swarm mode (not regular Compose).
Good for production, but more complex to set up.
File mounts (regular Compose):
You mount files from your host (VM) directly into the container.
The files are accessible at the path you specify (e.g., /run/secrets/db_password.txt).
Simpler, works everywhere, but files are visible on the host and inside the container.
Not encrypted or managed by Docker, so less secure for sensitive data.
If you have a secrets/ folder in your VM, mounting them is easiest and works with regular Compose. The only difference is security and management: file mounts are simple and flexible, Docker secrets are more secure but require Swarm.

For most student/learning setups, file mounts are fine. For production, prefer Docker secrets.

Benefits:

The container always finds the secret at a fixed path (/run/secrets/db_password.txt), regardless of where your project is on the host.
You can keep your secrets outside the project folder for security or organization.
Using /run/secrets is a convention, making your setup compatible with Docker Swarm secrets if you switch later.
If you read from ./secrets inside the container, you must ensure that folder exists and is mounted. Mounting to /run/secrets is clearer, more secure, and more portable.