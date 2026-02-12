/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_and_pipe.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:01:01 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/23 19:01:01 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

/**
 * Frees allocated memory for the argv array.
 */
static void	free_args(char **argv, int count)
{
	int	i;

	i = 1;
	while (i < count)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static	void	helper_free(char **args, int i, char *cmd_path)
{
	perror("Failed to allocate memory for argument.");
	free_args(args, i);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

/**
 * Allocates and fills the argv array based on the splitted_command array.
 */
static char	**prepare_command_args(char *cmd_path, char **splitted_cmd, int cnt)
{
	char	**args;
	int		i;

	args = malloc((cnt + 1) * sizeof(char *));
	if (!args)
	{
		perror("Failed to allocate memory for args.");
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	args[0] = cmd_path;
	i = 1;
	while (i < cnt)
	{
		(void)splitted_cmd;
		args[i] = ft_strdup(splitted_cmd[i]);
		if (!args[i])
			helper_free(args, i, cmd_path);
		i++;
	}
	args[cnt] = NULL;
	return (args);
}

/**
 * Displays error message and exits with code 127.
 */
void	msg(char *name, char *message)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(message, 2);
	ft_putendl_fd(name, 2);
	exit(127);
}

/**
 * Executes the given command, handling errors appropriately.
 */
void	exec_command(char **env, char **splitted_cmd)
{
	char	*cmd_path;
	char	**args;
	int		i;

	if (!splitted_cmd[0] || splitted_cmd[0][0] == '\0')
	{
		ft_putendl_fd("pipex: permission denied:", 2);
		exit(127);
	}
	cmd_path = get_command_path(env, splitted_cmd[0]);
	if (!cmd_path)
		msg(splitted_cmd[0], ": command not found");
	i = 0;
	while (splitted_cmd[i])
		i++;
	args = prepare_command_args(cmd_path, splitted_cmd, i);
	execve(cmd_path, args, env);
	perror("execve failed");
	free_args(args, i);
	free(cmd_path);
	exit(EXIT_FAILURE);
}
