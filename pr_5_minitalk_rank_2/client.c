
#include "minitalk.h"

void	ft_error_handler(int i)
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

void	ft_send_terminator(int pid)
{
	static int	i = 0;

	if (i <= 8)
		if (kill(pid, SIGUSR1) == -1)
			ft_error_handler(0);
	i++;
}

void	ft_send_signal(int pid, char *str)
{
	static int	bit = 0;
	static char	*str_cpy = 0;
// !!! NB
// if (str): The function only updates str_cpy if a new string is provided (str is not NULL).
	if (str)
		str_cpy = str;
	if (*str_cpy)
	{
		if ((((unsigned char)*str_cpy >> bit) % 2) == 0)
			if (kill(pid, SIGUSR1) == -1)
				ft_error_handler(0);
		if ((((unsigned char)*str_cpy >> bit) % 2) == 1)
			if (kill(pid, SIGUSR2) == -1)
				ft_error_handler(0);
		bit++;
		if (bit == 8)
		{
			str_cpy++;
			bit = 0;
		}
	}
	if (!(*str_cpy))
		ft_send_terminator(pid);
}

void	ft_receipt(int sig, siginfo_t *info, void *context)
{
	static int	id;

	if (info->si_pid != 0)
		id = info->si_pid;
	(void)context ;
	if (sig == SIGUSR1)
		ft_send_signal(id, NULL);
	if (sig == SIGUSR2)
		exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_receipt;
	// str_cpy retains the pointer to the string that was originally provided, even if subsequent calls pass NULL.
	if (sigaction(SIGUSR1, &action, NULL) == -1 
		|| sigaction(SIGUSR2, &action, NULL) == -1) // Registers the signal handler for the signals SIGUSR1 and SIGUSR2
		ft_error_handler(1);
	if (ac != 3)
	{
		write(1, "Use the format: ./client <PID> <String>\n", 39);
		exit(EXIT_FAILURE);
	}
	ft_send_signal(ft_atoi(av[1]), av[2]);
	while (1)
		pause();
	return (0);
}

/**
 * !!! NB !!!
 * sigaction(SIGUSR1, &action, NULL) function does not mean that the program is waiting until SIGUSR1 is received. Instead, this line of code is registering the signal handler (ft_receipt) to be called whenever SIGUSR1 or SIGUSR2 is received.
 * sigaction(SIGUSR1, &action, NULL);
This line tells the operating system that whenever the program receives SIGUSR1, it should call the signal handler defined in action, which is ft_receipt.
 * 
 * Declares a struct sigaction object named action to define the signal handling behavior.This object will be used to specify how the program handles specific signals (SIGUSR1 and SIGUSR2).
 * Sets the flag SA_SIGINFO to indicate that additional signal information should be provided to the signal handler.
This means that the siginfo_t structure will be passed to the signal handler, which can provide extra details about the signal, such as the sender's PID.
pause() causes the program to sleep until a signal is received.
When the signal arrives, the appropriate signal handler (ft_receipt) is called.
This loop keeps the program running until it receives a signal that instructs it to terminate (e.g., SIGUSR2 in this case).

void	ft_receipt(int sig, siginfo_t *info, void *context) : the function is registered with sigaction() to handle SIGUSR1 and SIGUSR2 signals.
siginfo_t *info provides additional details about the incoming signal, including the PID of the process that sent the signal.
ft_send_signal(id, NULL): This tells the client to continue sending the next bit of the current character (or move to the next character if all bits of the current character have already been sent).
* In main:
After sending each bit, the client waits for an acknowledgment (SIGUSR1) from the server.
When the server sends SIGUSR1, the signal handler (ft_receipt()) is called.
The handler then calls ft_send_signal(id, NULL) to continue sending the next bit.
Since str is NULL, str_cpy remains unchanged, and the function continues from where it left off.

Initially, ft_send_signal(ft_atoi(av[1]), av[2]) is called with "hello sunny world".
str_cpy is set to point to "hello sunny world".
The function starts sending the first character ('h'), bit-by-bit.
After each bit, the server sends SIGUSR1 as acknowledgment.
Each time ft_receipt() receives SIGUSR1, it calls ft_send_signal(id, NULL).
Since str is NULL, str_cpy is not updated, and it continues from where it left off.
Once all 8 bits of 'h' are sent, str_cpy++ moves to the next character ('e').
This process continues until the entire string is sent.
*/