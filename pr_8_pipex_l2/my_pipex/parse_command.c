/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 10:08:38 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/23 19:13:09 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

char	**split_command(char *command)
{
	char	**result;

	result = ft_split(command, ' ');
	if (!result)
	{
		perror("error splitting command.");
		exit(EXIT_FAILURE);
	}
	return (result);
}
