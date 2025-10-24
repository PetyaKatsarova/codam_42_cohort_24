#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void close_prev_fd(int prev_fd)
{
	if (prev_fd != 0)
		close(prev_fd);
}

int picoshell(char ***cmds)
{
	int 	fds[2], prev_fd = 0, i = 0;
	pid_t	pid;

	while (cmds[i])
	{
		if (pipe(fds) == -1)
		{
			close_prev_fd(prev_fd);
			return 1;
		}
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
			// here are cloned fds and all
			if (prev_fd != 0)
			{
				dup2(prev_fd, STDIN_FILENO); // redirect prev fd to std in: input on terminal
				close(prev_fd);
			}
			if (cmds[i+1])
				dup2(fds[1], STDOUT_FILENO); // redirect all written on fds1 > std out:
			close(fds[0]);
			close(fds[1]);
			execvp(cmds[i][0], cmds[i]);
			exit(1); // if execvp fails
		}
		// parent process: 
		close_prev_fd(prev_fd);
		close(fds[1]);
		prev_fd = fds[0]; // read end
		i++;
	}
	close_prev_fd(prev_fd);
	while (wait(NULL) > 0); // wait all child processes to finish
	return 0;
}
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./a.out

// gcc picoshell.c
// ulimit -n 30
//valgrind -q --track-fds=yes --trace-children=yes ./a.out
int main(void)
{
    // Test case 1: ls | grep picoshell
    char *cmd1[] = {"ls", NULL};
    char *cmd2[] = {"grep", "picoshell", NULL};
    char **test1[] = {cmd1, cmd2, NULL};
    
    printf("Test 1: ls | grep picoshell\n");
    picoshell(test1);
    
    // Test case 2: echo squalala | cat | sed s/a/b/g
    char *cmd3[] = {"echo", "squalala", NULL};
    char *cmd4[] = {"cat", NULL};
    char *cmd5[] = {"sed", "s/a/b/g", NULL};
    char **test2[] = {cmd3, cmd4, cmd5, NULL};
    
    printf("\nTest 2: echo squalala | cat | sed s/a/b/g\n");
    picoshell(test2);
    
    return 0;
}
