/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 17:01:37 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/15 17:01:37 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_input(argc, argv) == false)
		return (1);
	if (set_table(&table, argv) == false)
		return (1);
	begin_feast(&table);
	clean_table(&table);
}
