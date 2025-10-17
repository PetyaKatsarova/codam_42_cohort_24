/**
 * ssignment name		:	sandbox
Expected files		:	sandbox.c
Allowed functions	:	fork, waitpid, exit, alarm, sigaction, kill,
						printf, strsignal, errno
===============================================================================

Write the following function:

#include <stdbool.h>
int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)

This function must test if the function f is a nice function or a bad function,
you will return 1 if f is nice , 0 if f is bad or -1 in case of an error in
your function.

A function is considered bad if it is terminated or stopped by a signal
(segfault, abort...), if it exit with any other exit code than 0 or if it
times out.

If verbose is true, you must write the appropriate message among the following:

"Nice function!\n"
"Bad function: exited with code <exit_code>\n"
"Bad function: <signal description>\n"
"Bad function: timed out after <timeout> seconds\n"

You must not leak processes (even in zombie state, this will be checked using
wait).

We will test your code with very bad functions.
 */

 #include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

volatile sig_atomic_t timeout_flag = 0;

void timeout_handler(int sig)
{
    (void)sig;
    timeout_flag = 1;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    pid_t pid;
    int status;
    struct sigaction sa;
    
    if (!f)
        return -1;
    
    // Set up timeout handler
    sa.sa_handler = timeout_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, NULL) == -1)
        return -1;
    
    pid = fork();
    if (pid == -1)
        return -1;
    
    if (pid == 0) // Child process
    {
        f();
        exit(0);
    }
    else // Parent process
    {
        timeout_flag = 0;
        alarm(timeout);
        
        if (waitpid(pid, &status, 0) == -1)
        {
            alarm(0);
            if (timeout_flag)
            {
                kill(pid, SIGKILL);
                waitpid(pid, NULL, 0); // Clean up zombie
                if (verbose)
                    printf("Bad function: timed out after %u seconds\n", timeout);
                return 0;
            }
            return -1;
        }
        
        alarm(0);
        
        if (WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0)
            {
                if (verbose)
                    printf("Nice function!\n");
                return 1;
            }
            else
            {
                if (verbose)
                    printf("Bad function: exited with code %d\n", exit_code);
                return 0;
            }
        }
        else if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            if (verbose)
                printf("Bad function: %s\n", strsignal(sig));
            return 0;
        }
    }
    
    return -1;
}