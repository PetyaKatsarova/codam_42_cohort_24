/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_end_of_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 02:11:14 by sreerink          #+#    #+#             */
/*   Updated: 2025/05/28 17:24:09 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_end_of_file(t_data *data)
{
	write(STDERR_FILENO, "exit\n", 5);
	enable_echoctl();
	error_exit(NULL, data->exit_status, data);
}
