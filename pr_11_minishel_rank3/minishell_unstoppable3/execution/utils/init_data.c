/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:38:18 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/28 17:24:09 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_data_one(t_data *data, int i, int **pipes, t_tree *tree)
{
	data->i = i;
	data->pipe_count = get_num_pipes(tree);
	data->pipes = pipes;
	data->tree = tree;
}

void	setup_t_datawo(t_data *data, pid_t *pids,
				t_node *cmd, t_env_list *env)
{
	data->pids = pids;
	data->cmd = cmd;
	if (data)
		data->env = env;
	else
		data->env = NULL;
}