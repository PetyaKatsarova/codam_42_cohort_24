#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

/**
 *  Signal Name: SIGKILL
    Signal Number: Typically 9 (defined in <signal.h>).
    Purpose: Immediately terminates a process, regardless of its state.
    Behavior:
    The target process cannot catch, block, or ignore SIGKILL.
    The kernel immediately terminates the process.

    WIFEXITED(status) is a macro used to determine if a child process terminated normally (i.e., by calling exit() or returning from main()). It is typically used in conjunction with the wait() or waitpid() functions.
    Evaluates to true (non-zero) if the child process terminated normally.
    When it is true, you can then use WEXITSTATUS(status) to retrieve the exit status of the child.

    A good program should have no memory leaks. If the program creates child processes, none of its child processes should have memory leaks either. So we need to make sure to free all allocated memory at the end of each of our program’s processes. If we kill our child processes with a signal, we should beware of which signal we choose: SIGTERM, SIGINT and SIGKILL don’t all have the same implications as far as memory leaks are concerned!

    Debugging a program that creates child processes can be pretty overwhelming. In particular, Valgrind will probably output a torrent of error messages, coming not only from the parent process but also from every child process. Thankfully, Valgrind offers the option to mute the errors coming from child processes: --child-silent-after-fork=yes. Once the parent process’ errors resolved, we can remove this option to check the errors coming from the children.

    https://42-cursus.gitbook.io/guide/rank-02/pipex/understand-pipex
*/

void    child_routine(void)
{
    printf("\e[36mChild: Hi! I'm a child. I'm in an infinite loop.\e[0m\n");
    while (1) // Infinite loop
        continue;
}

void kill_and_get_children(pid_t *pid)
{
    int status;
    int i;

    printf("Parent:beginning...\n");
    i = 0;
    while (i < 3)
    {
        kill(pid[i], SIGKILL); // typically 9
        i++;
    }

    printf("Parent: I killed all my children! Mwahahaaa!\n");

    i = 0;
    while (i < 3)
    {
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status))
            printf("Parent: Child [%d] terminated normally.\n", pid[i]);
        else if (WIFSIGNALED(status))
            printf("\e[31mParent: Child [%d] got the %d signal, SIGTERM\e[0m\n", pid[i], WTERMSIG(status));
        i++;
    }
}

int main(void)
{
    pid_t   pid[3];
    int     i;

    i = 0;
    while (i < 3)
    {
        pid[i] = fork();
        if (pid[i] == -1)
            return (EXIT_FAILURE);
        else if (pid[i] == 0)
            child_routine(); // endless loop
        else if (pid[i] > 0)
            printf("Parent: Child #%d created with pid = %d\n", i, pid[i]);
        usleep(1000);
        i++;
    }
    kill_and_get_children(pid);
    return (EXIT_SUCCESS);
}