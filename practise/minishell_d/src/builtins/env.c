/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   env.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/25 22:24:08 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/28 00:27:30 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_builtin(char **env)
{
	size_t	i;

	i = 0;
	if (!env)
		return (EXIT_SUCCESS);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i] || !env[i][5])
	{
		write(STDERR_FILENO, "minishell: env: No such file or directory\n", 42);
		return (127);
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
