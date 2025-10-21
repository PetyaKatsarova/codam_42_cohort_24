#include <stdbool.h>    // bool, true, false
#include <unistd.h>     // fork, alarm, exit
#include <sys/wait.h>   // waitpid, WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG
#include <signal.h>     // sigaction, SIGALRM, kill, SIGKILL
#include <stdio.h>      // printf
#include <string.h>     // strsignal
#include <errno.h>      // errno, EINTR
#include <stdlib.h>     // exit

/** -- SUBJECT --
    Allowed functions : fork, waitpid, exit, alarm, sigaction, kill,
        printf, strsignal, errno
    Write the following function:
    #include <stdbool.h>
    int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
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
    */

   /** -- THEORY --
    SIGALRM  // Signal number 14 - "Alarm signal"
    installs a custom signal handler for the SIGALRM signal.
    b4 sigaction: 
    alarm(5);sleep(10);  // Process gets KILLED after 5 seconds (default behavior)   
    after sigaction(SIGALRM, &sa, NULL);  // Install custom handler
    alarm(5);
    sleep(10);  // After 5 seconds: alarm_handler() runs, then continues
    */

    /*
     bad funcs: crashes, exits wrong or times out
     Some functions never finish (infinite loops)
     waitpid() would wait FOREVER without timeout, thats why alarm() solves it
    */

void alarm_handler(int sig){ (void)sig; }

/**
returns -1 if func err, 1 if good func, 0 if bad func(....)
*/
int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    struct sigaction    sa;
    pid_t               pid;
    int                 status;

    sa.sa_handler = alarm_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask); // dont block other signals
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
    alarm(timeout);
    if (waitpid(pid, &status, 0) == -1)
    {
        if (errno == EINTR)
        {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);
            alarm(0); // cancel alarm
            if (verbose)
                printf("Bad function: timed out after %u seconds\n", timeout);
            return 0;
        }
        alarm (0); // cancel on other errors
        return (-1);
    }
    alarm (0); // critical: cancel alarm after successful waitpid;
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
        int sig = WTERMSIG(status);
        if (verbose)
            printf("Bad function: %s\n", strsignal(sig));
        return 0;
    }
    return (-1);
}

void nice_function(void)
{
	// This function does nothing and exits normally (exit code 0)
	return;
}

void bad_function_exit_code(void)
{
	// This function exits with code 1 (failure)
	exit(1);
}

void bad_function_segfault(void)
{
	// This function causes a segmentation fault
	int *ptr = NULL;
	*ptr = 42;  // This will cause a segfault
}

void bad_function_timeout(void)
{
	// This function runs indefinitely
	while (1) {}
}

void bad_function_sleep(void)
{
	// This function sleeps for more than the timeout and gets killed by alarm handler
	sleep(5);  // Sleep for 5 seconds (assuming timeout is less than 5 seconds)
}

int main()
{
	int	result;

	printf("Test 1: Normal function (Nice)\n");
	result = sandbox(nice_function, 5, true);
	printf("Result: %d\n", result);  // Expected output: 1 ("Nice function!")

	printf("Test 2: Bad function (Exit code 1)\n");
	result = sandbox(bad_function_exit_code, 5, true);
	printf("Result: %d\n", result);  // Expected output: 0 ("Bad function: exited with code 1")

	printf("Test 3: Bad function (Segfault)\n");
	result = sandbox(bad_function_segfault, 5, true);
	printf("Result: %d\n", result);  // Expected output: 0 ("Bad function: Segmentation fault")

	printf("Test 4: Bad function (Timeout)\n");
	result = sandbox(bad_function_timeout, 2, true);  // Timeout after 2 seconds
	printf("Result: %d\n", result);  // Expected output: 0 ("Bad function: timed out after 2 seconds")
 
	printf("Test 5: Bad function (Killed by SIGKILL)\n");
	result = sandbox(bad_function_sleep, 2, true);  // Timeout after 2 seconds
	printf("Result: %d\n", result);  // Expected output: 0 ("Bad function: timed out after 2 seconds")

	return 0;
}
