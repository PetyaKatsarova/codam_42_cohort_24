/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_argv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/14 14:29:23 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 16:29:24 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_argv(char **argv)
{
	int	j;

	j = 1;
	while (argv[j])
	{
		free(argv[j]);
		j++;
	}
	free(argv);
}
