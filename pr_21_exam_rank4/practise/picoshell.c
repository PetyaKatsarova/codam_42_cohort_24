/* Assignment name:    picoshell
Expected files:        picoshell.c
Allowed functions:    close, fork, wait, exit, execvp, dup2, pipe
_

Write the following function:

int    picoshell(char *cmds[]);

The goal of this function is to execute a pipeline. It must execute each
commands [sic] of cmds and connect the output of one to the input of the
next command (just like a shell).

Cmds contains a null-terminated list of valid commands. Each rows [sic]
of cmds are an argv array directly usable for a call to execvp. The first
arguments [sic] of each command is the command name or path and can be passed
directly as the first argument of execvp.

If any error occur [sic], The function must return 1 (you must of course
close all the open fds before). otherwise the function must wait all child
processes and return 0. You will find in this directory a file main.c which
contain [sic] something to help you test your function.


Examples: 
./picoshell /bin/ls "|" /usr/bin/grep picoshell
picoshell
./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'
squblblb/
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void close_prev_fd(int prev_fd)
{
    if (prev_fd)
        close(prev_fd);
}

int picoshell(char **cmds[])
{
    int fds[2], prev_fd = 0, i = 0;
    pid_t pid;

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
            close_prev_fd(prev_fd);
            close(fds[0]);
            close(fds[1]);
            return 1;
        }
        if (pid == 0)
        {
            if (prev_fd)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmds[i+1])
                dup2(fds[1], STDOUT_FILENO);
            close(fds[0]);
            close(fds[1]);
            fprintf(stderr, "Executing: %s\n", cmds[i][0]);
            execvp(cmds[i][0], cmds[i]);
            fprintf(stderr, "execvp failed for: %s\n", cmds[i][0]);
    		perror("execvp");
            exit (1); // in case of err, otherwise execvp exits
        }
        close(fds[1]);
        close_prev_fd(prev_fd);
        prev_fd = fds[0];
        i++;
    }
    close_prev_fd(prev_fd);
    while (wait(NULL) > 0); // wait for all child pr to finish
    return 0;
}



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