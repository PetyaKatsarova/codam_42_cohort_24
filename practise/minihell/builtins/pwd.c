/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:04:45 by nmedeiro          #+#    #+#             */
/*   Updated: 2025/05/28 17:24:09 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(int fd, t_parser *parser, t_data *data)
{
	char	*path;

	if (parser->cmd[1] != NULL)
	{
		ft_putendl_fd(STDERR_FILENO, "pwd: too many arguments");
		data->exit_code = 1;
		return ;
	}
	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		ft_putendl_fd(fd, path);
		free(path);
	}
}
