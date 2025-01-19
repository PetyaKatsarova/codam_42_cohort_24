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
		perror(file_name);
		exit(EXIT_FAILURE);
	}

	if (mode == 'x' && (access(file_name, F_OK) != 0 || access(file_name, X_OK) != 0))
	{
		perror(file_name);
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

// char	**split_command(char *command)
// {
// 	char	**result;

// 	result = ft_split(command, ' ');
// 	if (!result)
// 	{
// 		perror("error splitting command.");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (result);
// }

// Print an error message and exit if a fork fails
void	print_err_exit(int pid)
{
	if (pid == -1)
	{
		perror("fork failed"); // TODO
		exit(EXIT_FAILURE);
	}
}

// Split command by quotes, then by spaces outside quotes
// Updated quote handling inside split_command function
char	**split_command(char *command)
{
	char	**quote_split;
	char	**final_result;
	int		total_count, i;

	if (!ft_strchr(command, '\'') && !ft_strchr(command, '\"'))
		return (ft_split(command, ' '));
	if (ft_strchr(command, '\"'))
		quote_split = ft_split(command, '\"');
	else if (ft_strchr(command, '\''))
		quote_split = ft_split(command, '\'');
	i = -1;
	total_count = 0;
	while (quote_split[++i])
	{
		total_count += (i % 2 == 0) 
			? count_tokens(ft_split(quote_split[i], ' ')) 
			: 1;
	}

	final_result = malloc((total_count + 1) * sizeof(char *));
	if (!final_result)
		return (free_dbl_ptr(quote_split), NULL);

	process_split_parts(quote_split, final_result);
	return (free_dbl_ptr(quote_split), final_result);
}
