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
    charline;
    while(line = get_next_line(fd))
        ft_putstr(line);
}
Hint: Do not leak file descriptors!
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int    ft_popen(const char *file, char const *argv[], char type)
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
		if (type == 'r')
		{
			if (dup2(fds[1], 1) == -1) //write
				exit(1);
			
		}
		else
		{
			if (dup2(fds[0], 0) == -1)
				exit(1);
		}
		close(fds[0]);
		close(fds[1]);
		execvp(file,  (char *const*)argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(fds[1]);
		return fds[0];
	}
	if (type == 'w')
	{
		close(fds[0]);
		return (fds[1]);
	}
	return (-1);
}

int main() {
    int fd = ft_popen("ls", (char const[]){"ls", NULL}, 'r');
    char line;
    while(line = get_next_line(fd))
        ft_putstr(line);
}

