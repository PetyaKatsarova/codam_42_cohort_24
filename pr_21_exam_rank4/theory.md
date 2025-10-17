Syscalls are system calls like malloc, calloc, write, etc. If they fail, exit with code 1:

node *ret = calloc(1, sizeof(node));
if (!ret)
    exit(1);  // Syscall failure