#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h> // printf

void signal_handler(int sig) { (void)sig; }
/*
return 1 if f is nice , 0 if f is bad or -1 in case of an error in
your function.
*/
int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    struct  sigaction sa;
    int     status;
    pid_t   pid;

    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1)
        return (-1);
    pid = fork();
    if (pid == -1)
        return (-1);
    if (pid == 0)
    {
       f();
       exit(0);
    }
    /*Start timer, Wait for child function to finish, If timer goes off → function is stuck → KILL IT!*/
    alarm(timeout);
    /* waitpid() == -1 when:
     Child process doesn't exist
     Permission denied
     SIGALRM interrupted it (our case!)
    */
    if (waitpid(pid, &status, 0) == -1)
    {
        if (errno == EINTR) // interrupted by a signal
        {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0); // wait for the killed child to clean up
            alarm(0);
            if (verbose)
                 printf("Bad function: timed out after %u seconds\n", timeout);
            return 0;
        }
        alarm (0);
        return (-1);
    }
    alarm(0);
    if (WIFEXITED(status))
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
    if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status); //Extracts the signal number that killed a child process
        if (verbose)
            printf("Bad function: %s\n", strsignal(sig)); //returns a string describing the signal number passed in the argument sig
        return 0;
    }
    return (-1);
}