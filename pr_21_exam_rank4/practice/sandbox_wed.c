/*
Assignment name  : sandbox
Expected files  : sandbox.c
Allowed functions : fork, waitpid, exit, alarm, sigaction, kill,
      printf, strsignal, errno

Write the following function:
#include <stdbool.h>
int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
This function must test if the function f is a nice function or a bad function,
you will return 1 if f is nice , 0 if f is bad or -1 in case of an error in
your function.
If verbose is true, you must write the appropriate message among the following:
"Nice function!\n"
"Bad function: exited with code <exit_code>\n"
"Bad function: <signal description>\n"
"Bad function: timed out after <timeout> seconds\n"
You must not leak processes (even in zombie state, this will be checked using
wait).
We will test your code with very bad functions.

A function is considered bad if it is terminated or stopped by a signal
(segfault, abort...), if it exit with any other exit code than 0 or if it
times out.
*/
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

void signal_h(int sig) { (void)sig; }

// return 1 if a nice func
int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    pid_t   pid;
    int     status;
    struct sigaction sa;

    sa.sa_handler = signal_h;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1) // dont block sth?
        return (-1);
    pid = fork();
    if (pid == -1)
        return (-1);
    if (pid == 0)
    {
        f();
        exit(0);
    }
    alarm(timeout);
    if (waitpid(pid, &status, 0) == -1) // CASE 1
    {
        if (errno == EINTR)
        {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);
            alarm(0);
            if (verbose)
                printf("Bad function: timed out after %u seconds\n", timeout);
            return 0;
        }
        alarm(0);
        return (-1);
    }
    alarm(0);
    if (WIFEXITED(status)) // case 2
    {
        if (WEXITSTATUS(status) == 0)
        {
            if (verbose)
                printf("Nice function!\n");
            return 1;
        }
        else
        {
            if (verbose)
                printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
            return 0;
        }
    }
    if (WIFSIGNALED(status)) // case 3
    {
        int sig = WTERMSIG(status);
        if (verbose)
            printf("Bad function: %s\n", strsignal(sig));
        return (0); // good func but interrupted by signal and not timedout
    }
    return (-1)
}