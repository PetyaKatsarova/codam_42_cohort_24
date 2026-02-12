/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sandbox_explained.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/17 18:32:06 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/10/23 18:10:24 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * THEORY:
 * WIFEXITED(status)
What it stands for:
W = Wait (from waitpid family)
IF = If
EXITED = Process exited normally
if (WIFEXITED(status)) {Process called exit() or returned from main()}
Tests if child process terminated normally (not killed by signal)
Returns true if child called exit() or returned from main()
Returns false if child was killed by signal (segfault, SIGKILL, etc.)
------------------------------------------------------------------------
WEXITSTATUS(status)
What it stands for:
W = Wait
EXIT = Exit
STATUS = Status code
if (WIFEXITED(status)){int exit_code = WEXITSTATUS(status); } Extract the exit code (0-255)
Extracts the exit code that child passed to exit()
Only valid if WIFEXITED(status) is true
Range: 0-255 (8-bit value)
Convention: 0 = success, non-zero = failure
// Child:
exit(0);    // Success
exit(1);    // General failure
exit(127);  // Command not found

// Parent:
int code = WEXITSTATUS(status);
if (code == 0)
    printf("Success!");
else
    printf("Failed with code %d", code);
-------------------------------------------------------------------------
EINTR (errno value)
What it stands for:
E = Error
INTR = Interrupted
System call was interrupted by a signal
Many blocking system calls can be interrupted
When signal arrives, system call stops and returns -1
errno is set to EINTR to indicate "interrupted, not failed"
// These calls can be interrupted by signals:
read(fd, buffer, size);     // Reading from file/socket
write(fd, buffer, size);    // Writing to file/socket  
waitpid(pid, &status, 0);   // Waiting for child process
sleep(seconds);             // Sleeping
select()/poll();            // Waiting for I/O
alarm(timeout);  // Schedule SIGALRM
if (waitpid(pid, &status, 0) == -1)  // Gets interrupted when alarm fires
{
    if (errno == EINTR)  // "Aha! Alarm went off = timeout!"
        handle_timeout();
}
 */

#include <stdbool.h>    // bool, true, false
#include <unistd.h>     // fork, alarm, exit
#include <sys/wait.h>   // waitpid, WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG
#include <signal.h>     // sigaction, SIGALRM, kill, SIGKILL
#include <stdio.h>      // printf
#include <string.h>     // strsignal
#include <errno.h>      // errno, EINTR
#include <stdlib.h>     // exit

// NB!! WRONG BUT USE THE THEORYA
/**
 *  This function does literally nothing except exist
	When SIGALRM arrives, it interrupts the blocking waitpid() call
	No global variables needed - the interruption itself is the message
 */
void	alarm_handler(int sig)
{
	(void)sig;
}
/*return 1 if f is nice , 0 if f is bad or -1 in case of an error in the function.

sigaction(SIGALRM, &sa, NULL);   1. Install handler FIRST 
alarm(timeout);                  2. Schedule alarm SECOND 
waitpid(pid, &status, 0);        3. Wait for child 
*/
int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction	sa;
	pid_t				pid;
	int					status;

		/*Set up signal handler after fork (cleaner design) */
	sa.sa_handler = alarm_handler; // Install our minimal handler
	sa.sa_flags = 0; //No special flags
	sigemptyset(&sa.sa_mask); //Don't block any signals during handler
	sigaction(SIGALRM, &sa, NULL);

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		f(); //If f() crashes, child dies with signal (segfault, etc.)
		exit(0);
	}
	// do i need to add else here or leave it?
	/*  alarm() arranges for a SIGALRM signal to be delivered to the calling process in seconds seconds.
       If seconds is zero, any pending alarm is canceled.
       In any event any previously set alarm() is canceled.*/
	alarm(timeout); // When alarm fires, SIGALRM is sent to parent process
	/*  waitpid(pid, &status, 0) blocks waiting for child to finish
		Normal case: Child finishes → waitpid() returns child's PID
		Timeout case: SIGALRM fires → interrupts waitpid() → returns -1
		errno == EINTR means "system call interrupted by signal"
		Timeout handling:
		kill(pid, SIGKILL) - Force-kill the stuck child
		waitpid(pid, NULL, 0) - Reap the zombie child
		Print timeout message and return 0 (bad function)
 */
/**
 * waitpid() was blocking
SIGALRM fires → interrupts waitpid()
waitpid() returns -1 
 */
	if (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
		{
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0);
		}
		return (-1);
	}
	//Child finished before timeout, so cancel the pending alarm.
	/* WIFEXITED(status) - True if child called exit() or returned normally
	  WEXITSTATUS(status) - Extract the exit code (0-255)
	  Exit code 0 = success → return 1 (nice function)
	  Exit code ≠ 0 = failure → return 0 (bad function) */
	if(WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		else
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
			return (0);
		}
	}
	/*  WIFSIGNALED(status) - True if child was killed by signal
		WTERMSIG(status) - Extract signal number (SIGSEGV, SIGABRT, etc.)
		strsignal(sig) - Convert signal to human-readable string
		Any signal termination = bad function → return 0 */
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (verbose)
			printf("Bad function: %s\n", strsignal(sig));
		return (0);
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
