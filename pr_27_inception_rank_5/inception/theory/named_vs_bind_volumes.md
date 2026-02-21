Docker named volumes are managed by Docker and are stored in a location controlled by Docker itself, not in a custom directory you specify. When you create and use a named volume (for example, mydata), Docker stores its data in its own storage area (typically under /var/lib/docker/volumes/ on the host), not in a directory like /home/me/data.

If you want to use a specific directory on your host (such as /home/me/data), you should use a bind mount instead of a named volume. Here’s how you can do that:

docker run -v /home/me/data:/container/path IMAGE

If you use a named volume, you cannot specify its location on the host. Named volumes are always managed by Docker and their location is not configurable through the Docker CLI or Compose file.

Summary:

Use a named volume if you want Docker to manage the storage location.
Use a bind mount if you want to use a specific directory on your host.
Sources:

https://docs.docker.com/engine/storage/volumes/
https://docs.docker.com/engine/storage/
https://docs.docker.com/reference/cli/docker/volume/create/
https://docs.docker.com/engine/containers/run/