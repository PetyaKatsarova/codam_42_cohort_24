/*
Allowed functions:	close, fork, wait, exit, execvp, dup2, pipe
int    picoshell(char **cmds[]);

The goal of this function is to execute a pipeline. It must execute each
commands of cmds and connect the output of one to the input of the
next command (just like a shell).
e
Cmds contains a null-terminated list of valid commands. Each rows
of cmds are an argv array directly usable for a call to execvp. The first
arguments of each command is the command name or path and can be passed
directly as the first argument of execvp.

If any error occur, The function must return 1 (you must of course
close all the open fds before). otherwise the function must wait all child
processes and return 0. You will find in this directory a file main.c which
contain something to help you test your function.
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void close_prev_fd(int prev_fd)
{
	if (prev_fd != 0)
		close(prev_fd);
}

int    picoshell(char **cmds[])
{
	int fds[2], prev_fd = 0, i = 0;
	pid_t pid;

	while (cmds[i])
	{
		if (pipe(fds) == -1)
			return (close_prev_fd(prev_fd), 1);
		pid = fork();
		if (pid == -1)
		{
			close(fds[0]);
			close(fds[1]);
			close_prev_fd(prev_fd);
			return 1;
		}
		if (pid == 0)
		{
			if (prev_fd != 0)
			{
				dup2(prev_fd, 0);
				close_prev_fd(prev_fd);
			}
			if (cmds[i+1])
				dup2(fds[1], 1);
			close(fds[1]);
			close(fds[0]);
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		close_prev_fd(prev_fd);
		prev_fd = fds[0];
		close(fds[1]);
		i++;
	}
	close_prev_fd(prev_fd);
	while (wait(NULL) > 0);
	return 0;
}
