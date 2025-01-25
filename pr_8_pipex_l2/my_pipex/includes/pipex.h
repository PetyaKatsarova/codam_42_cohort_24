/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/25 19:16:03 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/25 19:16:03 by pekatsar      ########   odam.nl         */
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

// helpers.c
int				is_valid_read_file(char *file_name, char mode);
void			free_dbl_ptr(char **ptr);
void			print_err_exit(int pid);
void			free_cmd2(char **cmd1, char **cmd2);
void			perr_exit(void);

// parsing_path.c
char			*get_command_path(char **env, char *command_no_flag);

// file_and_pipe.c
void			exec_command(char **env, char **splitted_command);

// parse_command.c
char			**split_command(char *command);

// libft functions
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
unsigned int	ft_strlen(const char *str);
char			*ft_strnstr(const char *haystack, const char *needle, \
				size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
void			*ft_memset(void *b, int c, size_t len);

#endif
