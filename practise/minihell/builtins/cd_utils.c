/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:00 by edribeir          #+#    #+#             */
/*   Updated: 2025/05/28 17:24:09 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_node(t_env *env, char *str)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(str, temp->key_word, strlen(str)) == 0)
			return (temp->info);
		temp = temp->next;
	}
	return (NULL);
}

bool	is_multiples_arg(t_parser *parser, t_data *data)
{
	if (parser->cmd[1] && parser->cmd[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putendl_fd(STDERR_FILENO, "Too many arguments");
		data->exit_code = 1;
		return (true);
	}
	return (false);
}
