/*
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
We will test your code with very bad functions.
*/

#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

void signal_handler(int sig) { (void)sig; }

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t 				pid;
	struct sigaction	sa;
	int					status;

	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
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
	alarm(timeout);
	if (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
		{
			alarm(0);
			kill (pid, SIGKILL);
			waitpid(pid, NULL, 0);
			if (verbose)
				printf("Bad function: timed out after %u seconds\n", timeout);
			return 0;
			
		}
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
		if (verbose)
			printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
		return (0);
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

void nice_f()
{
	return ;
}

int main()
{
	int result;

	result = sandbox(nice_f, 5, true);
	return 0;
}