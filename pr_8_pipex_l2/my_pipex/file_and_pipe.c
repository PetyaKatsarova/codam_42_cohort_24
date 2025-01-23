/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_and_pipe.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/14 13:42:50 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/17 18:38:49 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

/**
 * Frees allocated memory for the argv array.
 */
static void	free_args(char **argv, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/**
 * Allocates and fills the argv array based on the splitted_command array.
 */
static char	**prepare_command_args(char *command_path, char **splitted_command,
		int arg_count)
{
	char	**args;
	int		i;

	args = malloc((arg_count + 1) * sizeof(char *));
	if (!args)
	{
		perror("Failed to allocate memory for args.");
		free(command_path);
		exit(EXIT_FAILURE);
	}
	args[0] = command_path;
	i = 1;
	while (i < arg_count)
	{
		args[i] = ft_strdup(splitted_command[i]);
		if (!args[i])
		{
			perror("Failed to allocate memory for argument.");
			free_args(args, i);
			free(command_path);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (args[arg_count] = NULL, args);
}

void msg(char *name, char *message)
{

	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(message, 2);
	exit(127);
}

void    exec_command(char **env, char **splitted_command)
{
    char    *command_path;
    char    **args;
    int     i;

    if (!splitted_command[0] || splitted_command[0][0] == '\0')
    {
        ft_putendl_fd("pipex: permission denied:", 2);
        exit(127);
    }

    command_path = get_command_path(env, splitted_command[0]);
    if (!command_path)
		msg(splitted_command[0], ": command not found");
    i = 0;
    while (splitted_command[i])
        i++;
    args = prepare_command_args(command_path, splitted_command, i);
    execve(command_path, args, env);
    perror("execve failed");
    free_args(args, i);
    free(command_path);
    exit(EXIT_FAILURE);
}
