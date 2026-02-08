sudo dockerd &
dockerd = Docker daemon (the background service)
& = Run in background (don't wait for it to finish)
Purpose: Attempt to start Docker daemon immediately
Problem: Runs asynchronously, may not finish before next check

command -v = Check if a command exists in the system
systemctl = System control utility (modern Linux service manager)
&> /dev/null = Redirect all output to trash (silent check)

 if docker ps &> /dev/null; then

 // docker ps:
    Exit code 0 = Docker is running and accessible
    Exit code 1 = Docker is not running or permission denied