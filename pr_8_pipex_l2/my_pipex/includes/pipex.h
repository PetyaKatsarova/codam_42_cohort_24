/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 18:20:49 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/17 18:25:28 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

// helpers.c
int		is_valid_read_file(char *file_name, char mode);
void	free_dbl_ptr(char **ptr);
void	print_err_exit(int pid);
void    free_cmd2(char **cmd1, char **cmd2);
void    perr_exit();

// parsing_path.c
char	*get_command_path(char **env, char *command_no_flag);

// file_and_pipe.c
void	exec_command(char **env, char **splitted_command);

//parse_command.c
char	**split_command(char *command);

#endif
