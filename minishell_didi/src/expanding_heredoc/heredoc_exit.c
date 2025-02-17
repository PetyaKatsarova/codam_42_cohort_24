/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 20:16:15 by didi          #+#    #+#                 */
/*   Updated: 2024/10/01 22:22:28 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc_exit(char *str, int i)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '{')
		{
			i += 2;
			if (str[i] == '?')
				return (true);
			return (false);
		}
		if (str[i + 1] == '?')
			return (true);
	}
	return (false);
}

t_h_dol	*init_here_exit(char *str, int exit)
{
	t_h_dol	*new;

	new = malloc(sizeof(t_h_dol));
	if (!new)
		return (NULL);
	new->expanded = ft_itoa(exit);
	if (!new->expanded)
		return (NULL);
	new->env_name = NULL;
	new->copy = ft_strdup(str);
	if (!new->copy)
	{
		free(new->expanded);
		return (NULL);
	}
	new->i = 0;
	new->str_len = ft_strlen(str);
	new->start_env = 0;
	new->end_var = 0;
	new->brackets = false;
	new->no_closing_brackets = false;
	new->exp_kind = IS_EXIT;
	return (new);
}

void	process_here_exit(t_h_dol *info, bool *mal_fail)
{
	while (info->i < info->str_len)
	{
		if (info->copy[info->i] == '$' && (info->copy[info->i + 1] == '?' || \
			(info->copy[info->i + 1] == '{' && info->copy[info->i + 2] == '?')))
		{
			expand_here_exit(info->copy, info, mal_fail);
			if (*mal_fail)
				return ;
			expand_heredoc_string(info->copy, info, mal_fail);
			if (*mal_fail)
				return ;
			info->str_len = ft_strlen(info->copy);
			continue ;
		}
		info->i++;
		while (info->copy[info->i] && info->copy[info->i] != '$')
			info->i++;
		info->str_len = ft_strlen(info->copy);
	}
}
