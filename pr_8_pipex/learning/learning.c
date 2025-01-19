#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#ifndef CHILD_EXIT_CODE
# define CHILD_EXIT_CODE 42
#endif

#define EXPECTED_CODE 42

// https://42-cursus.gitbook.io/guide/rank-02/pipex/understand-pipex

void	child_routine(pid_t pid)
{
	printf("\e[36mChild: Hi! I'm the child. PID received from fork = %d\e[0m\n", 
			pid); // should be 0
	printf("\e[36mChild: Exiting with exit code %d.\e[0m\n",
			CHILD_EXIT_CODE);
	exit(CHILD_EXIT_CODE); // !! NB
}

void	parent_routine(pid_t pid)
{
    int status;

    printf("Parent: I'm the parent. PID received from fork = %d\n", pid); // the child pid
    printf("Parent: Waiting for my child to exit with PID [%d].\n", pid);
    waitpid(pid, &status, 0);
    printf("Parent: My child exited with status %d\n", status);

    if (WIFEXITED(status)) // If child exited normally
	{
		printf("Parent: My child's exit code is %d\n",
				WEXITSTATUS(status));
		if (WEXITSTATUS(status) == EXPECTED_CODE)
			printf("Parent: That's the code I expected!\n");
		else
			printf("Parent: I was not expecting that code...\n");
	}
}

int main()
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        return (EXIT_FAILURE);

    else if (pid == 0)
    {
        child_routine(pid);
    }
    else if (pid > 0)
    {
        parent_routine(pid);
    }
    return (EXIT_SUCCESS);
}


/**
 * pid_t fork(void)
 * the parent receives the child’s PID,
the child receives 0,
and in the event of an error, fork returns -1.

ps aux | grep 2299213 | grep "Z+"
Explanation:
ps aux: Lists all processes with detailed information.
grep 2299213: Filters processes containing 2299213.
grep "Z+": Filters the output further for processes with the Z+ state (zombie processes).
Zombie Process: Processes that have terminated but still have entries in the process table.
 * 
*/