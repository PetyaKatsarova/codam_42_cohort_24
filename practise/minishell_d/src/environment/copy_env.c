/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:37:19 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/28 00:03:35 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_env(char **env)
{
	char	**copy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	copy = ft_calloc(sizeof(char *), i + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (copy[i] == NULL)
		{
			free_array(copy);
			return (copy);
		}
		i++;
	}
	return (copy);
}
