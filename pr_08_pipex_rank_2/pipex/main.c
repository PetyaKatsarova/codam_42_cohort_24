/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:06:13 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/23 19:06:13 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static void	dup2_protect(int *pipe_fd)
{
	perror("dup2 failed");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(EXIT_FAILURE);
}

static void	execute_first_child(char **env, char **cmd1, char *infile,
		int *pipe_fd)
{
	int	input_fd;

	if (infile)
	{
		is_valid_read_file(infile, 'r');
		input_fd = open(infile, O_RDONLY);
		if (input_fd == -1)
		{
			perror("Failed to open input file");
			exit(EXIT_FAILURE);
		}
		if (dup2(input_fd, STDIN_FILENO) == -1)
			dup2_protect(pipe_fd);
		close(input_fd);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		dup2_protect(pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_command(env, cmd1);
}

static void	execute_second_child(char **env, char **cmd2, char *outfile,
		int *pipe_fd)
{
	int	output_fd;

	if (outfile)
	{
		output_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1)
		{
			perror("Failed to open output file");
			exit(EXIT_FAILURE);
		}
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			dup2_protect(pipe_fd);
		close(output_fd);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		dup2_protect(pipe_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	exec_command(env, cmd2);
}

static int	pipe_it(char **env, char **cmd1, char **cmd2, char **argv)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;
	int	status;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	print_err_exit(pid1);
	if (pid1 == 0)
		execute_first_child(env, cmd1, argv[1], pipe_fd);
	pid2 = fork();
	print_err_exit(pid2);
	if (pid2 == 0)
		execute_second_child(env, cmd2, argv[4], pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	status = 0;
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	return (process_status_protect(status));
}

int	main(int argc, char **argv, char **env)
{
	char	**cmd1;
	char	**cmd2;
	int		status;

	if (argc != 5)
	{
		ft_putstr_fd("Not correct number of args(need 5): ", 2);
		ft_putendl_fd("./pipex infile cmd1 cmd2 outfile", 2);
		return (EXIT_FAILURE);
	}
	cmd1 = split_command(argv[2]);
	if (!cmd1)
	{
		perror("split_command failed");
		return (-1);
	}
	cmd2 = split_command(argv[3]);
	free_cmd2(cmd1, cmd2);
	status = pipe_it(env, cmd1, cmd2, argv);
	free_dbl_ptr(cmd1);
	free_dbl_ptr(cmd2);
	return (status);
}
