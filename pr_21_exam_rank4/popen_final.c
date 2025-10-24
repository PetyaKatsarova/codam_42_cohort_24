
/* Allowed functions: pipe, fork, dup2, execvp, close, exit
write the following function:
    int    ft_popen(const char file, char const *argv[], char type)
The function must launch the executable file with the arguments argv (using execvp).
If the type is 'r' the function must return a file descriptor connected to the output of the command.
If the type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

Hint: Do not leak file descriptors!
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

 int    ft_popen(const char *file, char const *argv[], char type)
 {
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	int 	fds[2];
	pid_t	pid;

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
		if (type == 'r')
		{
			if (dup2(fds[1], 1) == -1)
				exit(1);
		}
		else if (type == 'w')
		{
			if (dup2(fds[0], 0) == -1)
				exit(1);
		}

		close(fds[0]);
		close(fds[1]);
		execvp(file, (char *const *)argv);
		exit (1);
	}
	if (type == 'r')
	{
		close(fds[1]);
		return (fds[0]);
	}
	else if (type == 'w')
	{
		close(fds[0]);
		return (fds[1]);
	}
	return (-1);
 }

int main()
{
    int fd = ft_popen("ls", (char const*[]){"ls", NULL}, 'r');
    if (fd != -1)
    {
        char buffer[1024];
        ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes > 0)
        {
            buffer[bytes] = '\0';
            printf("ls output:%s\n", buffer);
        }
        close(fd);
    }

    printf("Sort output:\n");
    fd = ft_popen("sort", (const char*[]){"sort", NULL}, 'w');
    if (fd != -1)
    {
        write(fd, "banana\napple\ncherry\n", 20);
        close(fd);
        wait(NULL);
        fflush(stdout); // ensure all output is displayed
    }
    return 0;
}