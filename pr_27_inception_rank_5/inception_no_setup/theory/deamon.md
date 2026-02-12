A daemon is a background process in Unix/Linux that runs independently of any terminal session.

Usually starts at boot (system startup).

Doesn’t interact directly with users.

Handles system-level tasks or long-running services (like web servers, databases, or print queues).

Examples: sshd, nginx, mysqld, cron.

Key Properties:

Background Process

Detaches from the controlling terminal.

Runs in the background continuously.

No Standard Input/Output

Daemons often redirect stdin/stdout/stderr to /dev/null or log files.

Parent Process

Most daemons are spawned by init (or systemd) at boot.

systemd is the modern way Linux manages daemons.

PID File

Many daemons create a PID file (e.g., /var/run/nginx.pid) to track their process ID.

Daemon Creation (Low-Level)

In C or Unix programming, creating a daemon usually involves:

Fork the process so the parent can exit.

Detach from the terminal:

setsid();


Change working directory to / (optional, avoids locking filesystems).

Close standard file descriptors (stdin, stdout, stderr).

Handle signals properly (SIGTERM for shutdown, etc.).

Simplified Example in Bash:

#!/bin/bash
# simple daemon example
while true; do
  echo "$(date) Running..." >> /tmp/daemon.log
  sleep 10
done &


The & runs it in the background.

Redirect output to a file instead of the terminal.

Pros:

Run tasks continuously without user intervention.

Essential for servers, schedulers, and services.

Can automatically restart on failure (with systemd or supervisord).

Cons / Risks:

Harder to debug since no terminal output.

Can consume resources indefinitely if misconfigured.

Requires careful logging and monitoring.

Poorly written daemons can hang or crash silently.

Daemon: background service running independently.

Use cases: servers, schedulers, monitoring tools.

Modern approach: systemd or containerized services instead of manually coding daemons.

Avoid if short-lived, interactive, or containerized tasks.