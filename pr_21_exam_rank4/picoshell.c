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
	while (wait(fds) > 0); // wait all child processes to finish
	return 0;
}
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./a.out

// gcc picoshell.c
// ulimit -n 30
//valgrind  --track-fds=yes --trace-children=yes ./a.out
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


	// int fd[2], prev_fd = 0, i = 0;
	// pid_t pid;

	// while (cmds[i])
	// {
	// 	if (pipe(fd) == -1)
	// 	{
	// 		if (prev_fd != 0)
	// 			close(prev_fd);
	// 		return 1;
	// 	}
	// 	pid = fork();
	// 	if (pid == -1)
	// 	{
	// 		close(fd[0]);
	// 		close(fd[1]);
	// 		if (prev_fd != 0)
	// 			close(prev_fd);
	// 		return 1;
	// 	}
	// 	if (pid == 0) // child
	// 	{
	// 		if (prev_fd != 0)
	// 		{
	// 			dup2(prev_fd, STDIN_FILENO); // 0
	// 			close(prev_fd);
	// 		}
	// 		if (cmds[i+1])
	// 			dup2(fd[1], STDOUT_FILENO); // 1
	// 		close(fd[0]);
	// 		close(fd[1]);
	// 		execvp(cmds[i][0], cmds[i]);
	// 		exit(1);
	// 	}

	// 	if (prev_fd != 0)
	// 		close(prev_fd);
	// 	close(fd[1]);
	// 	prev_fd = fd[0];
	// 	i++;
	// }
	// // close final read end
	// if (prev_fd != 0)
	// 	close(prev_fd);
	// while (wait(NULL) > 0);


// char ***parse_commands(char **argv)
// {
//     int cmd_count = 0, i = 0, j;
//     char ***commands;
    
//     // Count commands (separated by "|")
//     while (argv[i])
//     {
//         if (strcmp(argv[i], "|") == 0)
//             cmd_count++;
//         i++;
//     }
//     cmd_count++; // Last command after final "|"
    
//     commands = malloc(sizeof(char**) * (cmd_count + 1));
//     commands[cmd_count] = NULL;
    
//     int cmd_idx = 0, start = 0;
//     i = 0;
    
//     while (cmd_idx < cmd_count)
//     {
//         // Find end of current command
//         int end = start;
//         while (argv[end] && strcmp(argv[end], "|") != 0)
//             end++;
        
//         // Allocate space for this command
//         commands[cmd_idx] = malloc(sizeof(char*) * (end - start + 1));
        
//         // Copy arguments
//         for (j = 0; j < end - start; j++)
//             commands[cmd_idx][j] = argv[start + j];
//         commands[cmd_idx][end - start] = NULL;
        
//         start = end + 1; // Skip "|"
//         cmd_idx++;
//     }
    
//     return commands;
// }

//./a.out echo 'squalala' "|" cat "|" sed 's/a/b/g'
//./a.out /bin/ls "|" /usr/bin/grep picoshell
// int main(int argc, char **argv)
// {
//     if (argc < 2)
//     {
//         printf("Usage: %s cmd1 [args] | cmd2 [args] | ...\n", argv[0]);
//         return 1;
//     }
    
//     char ***commands = parse_commands(&argv[1]);
//     int result = picoshell(commands);
    
//     // Free allocated memory
//     for (int i = 0; commands[i]; i++)
//         free(commands[i]);
//     free(commands);
    
//     return result;
// }