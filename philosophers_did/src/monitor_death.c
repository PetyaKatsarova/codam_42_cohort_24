/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_death.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:59:57 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/11/12 23:39:02 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Waits for all philo threads to be active
static bool	all_threads_active(t_mtx *mutex, long *threads, long philo_num)
{
	bool	check;

	check = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_num)
		check = true;
	pthread_mutex_unlock(mutex);
	return (check);
}

// Check elapsed time since last meal and time_to_die.
// Convert time_to_die back to milliseconds.
static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	elapsed = get_time(MILLISECOND) - read_long(&philo->monitor_mutex, \
												&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1000;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

static bool	all_philos_full(t_table *table)
{
	bool	flag;

	flag = false;
	if (read_long(&table->table_mutex, &table->num_of_full_philos) \
					== table->num_of_philos)
		flag = true;
	return (flag);
}

// Continuously checks if any philosopher has died or if the philos are full. 
// It sets a shared flag (end_simulation) when the simulation should stop. 
// The philosopher threads check this flag to exit their cycles.
void	*monitoring_death(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_active(&table->table_mutex, &table->active_threads, \
								table->num_of_philos))
		;
	while (1)
	{
		i = -1;
		while (++i < table->num_of_philos)
		{
			if (philo_died(&table->philos[i]) || all_philos_full(table))
			{
				update_bool(&table->table_mutex, &table->end_simulation, true);
				if (philo_died(&table->philos[i]))
					print_activity(DIED, &table->philos[i]);
				return (NULL);
			}
		}
	}
	return (NULL);
}
