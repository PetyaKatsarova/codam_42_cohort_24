
#include "minitalk.h"

static void	ft_error_handler(int i)
{
	if (i == 0)
	{
		write(1, "Error KILL\n", 12);
		exit(1);
	}
	if (i == 1)
	{
		write(1, "Error SIGACTION\n", 17);
		exit(1);
	}
}

void	ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	val = 0;
	static int				bit = 1;
	static int				id = 0;

	if (info->si_pid != 0)
		id = info->si_pid;
	(void)context ;
	if (sig == SIGUSR1)
		val += 0; //try out TODO
	if (sig == SIGUSR2) // sig==1
		val += bit;
	bit <<= 1; // 1,2,4,8,16,32 etc
	if (bit == 256) //unsigned int bit from 0 to 255
	{
		bit = 1;
		if (val == 0)
			if (kill(id, SIGUSR2) == -1) // send receipt to sigusr2 that signal was recieved: reached end of str, exit success
				ft_error_handler(0); // err in signal
		if (val != 0)
			write(1, &val, 1);
		val = 0;
	}
	if (kill(id, SIGUSR1) == -1) //// send receipt to sigusr1 that signal was recieved: meaning keep sending
		ft_error_handler(0);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_signal_handler;
	pid = getpid();
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
	{
		ft_error_handler(1);
		return (1);
	}
	write(1, "PID = ", 6);
	ft_putnbr(pid);
	write(1, "\n", 1);
	// infinite loop to listen for signals:
	while (1)
		pause(); //makes the process sleep until it receives a signal.
	return (0);
}

/**
 * SIGUSR1 SIGUSR2:
 * Unlike typical forms of communication (such as sockets or pipes), signals do not carry payload data directly.
Instead, they serve as notifications.
The information is encoded in the way the signals are used. In this case, SIGUSR1 and SIGUSR2 represent binary values (0 and 1).
SIGUSR1 is typically signal number 10, and SIGUSR2 is usually signal number 12 (though exact numbers may vary depending on the system).
User-Defined:
They don’t have a predefined function or action associated with them.
It is entirely up to the programmer to define what actions a process should take upon receiving SIGUSR1 or SIGUSR2.
After receiving and processing a signal, the server sends back SIGUSR1 to the client as an acknowledgment.
This synchronization helps ensure the client knows that the server is ready for the next bit.
 * 
 * kill(pid_t pid, int signal):
The kill() function is used to send a signal to a process.
The first argument (pid) is the process ID of the target process.
The second argument (signal) is the signal to be sent to the target process.

exit() is een functie uit de standaardbibliotheek van C (<stdlib.h>).
Wanneer exit() wordt aangeroepen, doet het het volgende:
Beëindigt het Programma: Het beëindigt het programma onmiddellijk, zonder terug te keren naar het punt waar het werd aangeroepen.
Voert Opruiming Uit: Het sluit alle geopende bestanden, leegt buffers en voert eventuele functies uit die zijn geregistreerd met atexit().
Geeft Controle Terug aan het OS: Het geeft een exit-statuscode door aan het besturingssysteem om aan te geven hoe het programma is beëindigd.
void exit(int status);
status: Dit is de exitcode die aangeeft waarom het programma is beëindigd.
Het is een geheel getal en verschillende waarden geven verschillende informatie door aan het systeem of aanroepende proces.
exit(0): Wordt conventioneel gebruikt om succesvolle uitvoering aan te geven.
exit(1) of een andere niet-nul waarde: Geeft aan dat er een fout of abnormale toestand is opgetreden.

The first parameter is the signal (SIGUSR1 or SIGUSR2) that we want to handle.
The second parameter is a pointer to the action structure, which defines how the signal should be handled.
The third parameter is NULL, indicating that we do not want to save the previous signal action.
If sigaction() returns -1, it indicates an error. This might happen if the signal is invalid or there are insufficient permissions.
 * 

 The function pause() is a system call that makes the process sleep indefinitely until it receives a signal.
When the process is put to sleep with pause(), it stops executing further instructions and remains in a waiting state.

When a signal is sent to the process (e.g., SIGUSR1 or SIGUSR2), the operating system wakes up the process.
The operating system then triggers the signal handler that has been registered for that particular signal. In this case, the registered handler is ft_signal_handler.

The signal handler (ft_signal_handler) is automatically invoked by the operating system when the signal is received.
The function ft_signal_handler processes the signal—such as accumulating bits to form a character or printing out a value.

siginfo_t is typically used with the sigaction() system call, so the relevant documentation can be found under the manual page for sigaction.

The program starts and sets up the signal handler using sigaction().
The program enters an infinite loop and calls pause().
The process waits (is put to sleep) until it receives a signal.
When a signal (SIGUSR1 or SIGUSR2) arrives, the operating system wakes up the process and invokes ft_signal_handler.
After the handler (ft_signal_handler) finishes processing the signal, the flow returns to after pause().
The loop runs again, and pause() is called to wait for the next signal.

struct sigaction is a structure used to define how a program should respond to certain signals.
It allows the programmer to specify:
Which function should be called when a particular signal is received.
Whether additional information about the signal (siginfo_t) should be provided to the signal handler.
action.sa_flags = SA_SIGINFO;
action.sa_sigaction = ft_signal_handler;
action.sa_flags = SA_SIGINFO:
This flag indicates that the extended signal handling mechanism is being used.
Specifically, it tells the operating system that the signal handler will be using additional information provided via a siginfo_t structure.
Because SA_SIGINFO is set, the signal handler function must have a specific signature that takes three parameters:
void ft_signal_handler(int sig, siginfo_t *info, void *context);
The connection between struct sigaction and siginfo_t is that by using SA_SIGINFO, the system knows to provide extra information about the signal in the form of a siginfo_t structure to the handler function, enabling richer and more informative signal handling.
struct siginfo_t
siginfo_t is a structure that contains information about the signal that was received. It gives additional context about the origin and purpose of the signal.
struct sigaction is used to define the action to take when a specific signal is received. It provides a way to set a handler, flags, and masks that control how signals are handled.
siginfo_t *info: A pointer to a structure containing additional information about the signal (e.g., the PID of the process that sent the signal).
action.sa_sigaction = ft_signal_handler:
You are assigning the address of your signal handler function (ft_signal_handler) to the sa_sigaction field.
The sa_sigaction field is used for handlers that need more information about the signal (such as the sending process).
sigaction(SIGUSR1, &action, NULL):
This call to sigaction() tells the operating system that when the signal SIGUSR1 is received, the action described by action should be taken.
The second argument (&action) points to the struct sigaction you defined.
The third argument is used to store the previous action associated with the signal, but it is NULL here because we don’t need to save it.
You use struct sigaction to define the signal handling behavior.
Set action.sa_flags to SA_SIGINFO and set action.sa_sigaction to your signal handling function (ft_signal_handler).
Register Handler with sigaction():

sigaction(SIGUSR1, &action, NULL) registers the handler for SIGUSR1.
The operating system stores this information.
Signal Received:

When the process receives SIGUSR1, the operating system:
Looks up the handler in the signal table for the process.
Since the SA_SIGINFO flag was set, it knows that it must call ft_signal_handler(int sig, siginfo_t *info, void *context).
The system calls ft_signal_handler() with the appropriate parameters, providing detailed information through the siginfo_t pointer.
*/
