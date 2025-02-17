/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 16:58:59 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/11/12 20:34:51 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks whether the input meets minimum standards.
// ft_atol sets the value to -1 in case of > INT_MAX
static bool	validate_table_values(t_table *table)
{
	if (table->num_of_philos == 0)
		return (error_bool("Have at least 1 philosopher"));
	if (table->num_of_philos == -1 || table->time_to_die == -1 || \
		table->time_to_eat == -1 || table->time_to_sleep == -1)
		return (error_bool("Number is > than INT_MAX"));
	if (table->num_of_philos > 200)
		return (error_bool("Number of philos is > 200"));
	if (table->limited_dinner == true && table->num_limit_meals == -1)
		return (error_bool("Number is > than INT_MAX"));
	else if (table->time_to_die < 60000 || table->time_to_eat < 60000 || \
		table->time_to_sleep < 60000)
		return (error_bool("Use timestamps bigger than 60 ms"));
	if (table->limited_dinner == true && table->num_limit_meals == 0)
		return (error_bool("Given limited meals is 0"));
	return (true);
}

// We set and validate all given values.
// Our input is millisecs, so we multiply * 1000 to convert
// to microsecs for usleep and gettimeofday.
bool	initialize_input(t_table *table, char **argv)
{
	table->num_of_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	table->active_threads = 0;
	table->philos_ready = false;
	table->limited_dinner = false;
	table->num_limit_meals = -1;
	table->num_of_full_philos = 0;
	if (argv[5])
	{
		table->num_limit_meals = ft_atol(argv[5]);
		table->limited_dinner = true;
	}
	if (validate_table_values(table) == false)
		return (false);
	return (true);
}
