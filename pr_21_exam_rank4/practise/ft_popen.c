/**
ft_popen
/* Allowed functions: pipe, fork, dup2, execvp, close, exit
write the following function:
    int    ft_popen(const char file, char const *argv[], char type)
The function must launch the executable file with the arguments argv (using execvp).
If the type is 'r' the function must return a file descriptor connected to the output of the command.
If the type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.
example:
int main() {
    int fd = ft_popen("ls", (char const[]){"ls", NULL}, 'r');
    char line;
    while(line = get_next_line(fd))
        ft_putstr(line);
}
Hint: Do not leak file descriptors!
*/

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int    ft_popen(const char *file, char *argv[], char type)
{
    if (!file || !argv || (type != 'r' && type != 'w'))
        return (-1);
    int fds[2];
    pid_t pid;

    if (pipe(fds) == -1)
        return (-1);
    pid = fork();
    if (pid == -1)
    {
        close(fds[0]);
        close(fds[1]);
        return (-1);
    }
    if (pid == 0)
    {
        if (type =='r')
        {
            dup2(fds[1], 1);
            close(fds[1]);
            close(fds[0]);
        }
        else if (type == 'w')
        {
            dup2(fds[0], 0);
            close(fds[1]);
            close(fds[0]);
        }
        execvp(file, argv);
        exit(1);
    }
    if (type == 'r')
    {
        close(fds[1]);
        wait(NULL);
        return (fds[0]);
    }
    else
    {
        close(fds[0]);
        return (fds[1]);
    }
}

int main() {
    // Test  read command output
    int fd = ft_popen("ls", (char*[]){"ls", NULL}, 'r');
    if (fd != -1) {
        char buffer[1024];
        ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            printf("ls output:\n%s\n", buffer);
        }
        close(fd);
    }
    
    // Test write to command input
    printf("Sort output:\n");
    fd = ft_popen("sort", (char*[]){"sort", NULL}, 'w');
    if (fd != -1) {
        write(fd, "banana\napple\ncherry\n", 20);
        close(fd);      // Signal EOF to sort
        wait(NULL);     // Wait for sort to finish processing
        fflush(stdout); // Ensure all output is displayed
    }
    
    return 0;
}