/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_updates.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 19:45:02 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/11/12 22:01:51 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_bool(t_mtx *mutex, bool *bool_condition, bool new_status)
{
	pthread_mutex_lock(mutex);
	*bool_condition = new_status;
	pthread_mutex_unlock(mutex);
}

void	update_long(t_mtx *mutex, long *long_value, long new_value)
{
	pthread_mutex_lock(mutex);
	*long_value = new_value;
	pthread_mutex_unlock(mutex);
}

bool	read_bool(t_mtx *mutex, bool *bool_condition)
{
	bool	read_value;

	pthread_mutex_lock(mutex);
	read_value = *bool_condition;
	pthread_mutex_unlock(mutex);
	return (read_value);
}

long	read_long(t_mtx *mutex, long *value)
{
	long	read_value;

	pthread_mutex_lock(mutex);
	read_value = *value;
	pthread_mutex_unlock(mutex);
	return (read_value);
}

// This function check whether or not the simulation is finished.
bool	dinner_finished(t_table *table)
{
	return (read_bool(&table->table_mutex, &table->end_simulation));
}
