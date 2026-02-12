/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:04:02 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/23 19:04:02 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

/*
 * Checks if the file exists and has the read and execute permissions.
 * Returns 1 if valid, otherwise exits with an error message and 0
 */
int	is_valid_read_file(char *file_name, char mode)
{
	if (mode == 'r' && (access(file_name, F_OK) != 0
			|| access(file_name, R_OK) != 0))
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	if (mode == 'x' && (access(file_name, F_OK) != 0
			|| access(file_name, X_OK) != 0))
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	return (1);
}

/**
 * Frees a double pointer and its elements.
 */
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

/**
 * Frees cmd1 if cmd2 allocation fails and exits with an error.
 */
void	free_cmd2(char **cmd1, char **cmd2)
{
	if (!cmd2)
	{
		free_dbl_ptr(cmd1);
		perror("split_command failed");
		exit(EXIT_FAILURE);
	}
}

/**
 * Prints an error message and exits if fork fails.
 */
void	print_err_exit(int pid)
{
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
}

/**
 * Processes the status and checks for normal termination.
 */
int	process_status_protect(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
	{
		perror("Child process did not terminate normally");
		return (1);
	}
}
