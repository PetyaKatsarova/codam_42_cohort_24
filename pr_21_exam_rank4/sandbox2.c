#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void alarm_handler(int sig)
{
    (void)sig;  // Just suppress unused warning
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    struct sigaction sa;
    pid_t pid;
    int status;

    // Setup signal handler
    sa.sa_handler = alarm_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1)  // FIX 2 & 4
        return (-1);

    pid = fork();
    if (pid == -1)
        return (-1);

    if (pid == 0)  // Child
    {
        f();
        exit(0);
    }

    // Parent
    alarm(timeout);

    if (waitpid(pid, &status, 0) == -1)
    {
        if (errno == EINTR)  // FIX 3: Use == not =
        {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);
            alarm(0);  // FIX 5: Cancel alarm
            if (verbose)
                printf("Bad function: timed out after %u seconds\n", timeout);  // FIX 6
            return 0;
        }
        alarm(0);  // Cancel on other errors
        return (-1);
    }

    alarm(0);  // FIX 5: CRITICAL - Cancel alarm after successful waitpid!

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
            if (verbose)  // FIX 7: Remove duplicate
                printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
            return 0;
        }
    }

    if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);  // FIX 8: Use WTERMSIG, not WIFSIGNALED
        if (verbose)
            printf("Bad function: %s\n", strsignal(sig));
        return 0;
    }

    return (-1);
}