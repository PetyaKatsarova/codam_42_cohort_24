/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nia_signals.c                                     :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/13 17:50:26 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/03 21:53:45 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	nia_sigint_handler(int sig)
{
	(void)sig;
}

void	nia_sigquit_handler(int sig)
{
	(void)sig;
}

void	set_signals_nia_mode(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	enable_echoctl();
	sa_int.sa_handler = &nia_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = &nia_sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
