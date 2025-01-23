/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/14 14:51:25 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/17 18:26:33 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

// Check if the file exists and has read permissions
int	is_valid_read_file(char *file_name, char mode)
{
	if (mode == 'r' && (access(file_name, F_OK) != 0 || access(file_name, R_OK) != 0))
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}

	if (mode == 'x' && (access(file_name, F_OK) != 0 || access(file_name, X_OK) != 0))
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	return (1);
}

// Free a double pointer and its elements
void	free_dbl_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_cmd2(char **cmd1, char **cmd2)
{
	if (!cmd2)
	{
		free_dbl_ptr(cmd1);
		perror("split_command failed");
		exit(EXIT_FAILURE);
	}
}

// Print an error message and exit if a fork fails
void	print_err_exit(int pid)
{
	if (pid == -1)
	{
		perror("fork failed"); // TODO
		exit(EXIT_FAILURE);
	}
}

