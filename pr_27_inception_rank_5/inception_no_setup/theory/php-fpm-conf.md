[www]
listen = 0.0.0.0:9000
user = www-data
group = www-data
pm = dynamic
pm.max_children = 5
pm.start_servers = 2
pm.min_spare_servers = 1
pm.max_spare_servers = 3

# pm stands for process manager in PHP-FPM. It controls how PHP worker processes are spawned and managed.

# pm = dynamic → PHP-FPM creates processes dynamically based on load.

# pm.max_children → maximum simultaneous PHP processes.

# pm.start_servers → number of PHP processes started at launch.

# pm.min_spare_servers → minimum idle processes to keep ready.

# pm.max_spare_servers → maximum idle processes allowed.

# It basically controls PHP performance and resource usage.
