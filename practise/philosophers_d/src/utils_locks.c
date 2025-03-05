/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_locks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 20:52:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/11/12 22:03:45 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function either locks or unlocks both forks.
bool	toggle_lock_and_fork(t_locker latch, t_status activity, t_philo *philo)
{
	if (activity == EATING)
	{
		if (latch == LOCK)
		{
			pthread_mutex_lock(&philo->first_fork->fork);
			print_activity(TAKEN_FIRST_FORK, philo);
			if (philo->table->num_of_philos == 1)
			{
				hyper_sleep(philo->table->time_to_die, philo->table);
				return (false);
			}
			pthread_mutex_lock(&philo->second_fork->fork);
			print_activity(TAKEN_SEC_FORK, philo);
		}
		else if (latch == UNLOCK)
		{
			pthread_mutex_unlock(&philo->first_fork->fork);
			pthread_mutex_unlock(&philo->second_fork->fork);
		}
	}
	return (true);
}

// Increases the number of threads running.
void	increase_active_threads(t_mtx *mutex, long *philo_threads)
{
	pthread_mutex_lock(mutex);
	(*philo_threads)++;
	pthread_mutex_unlock(mutex);
}

// pthread_join only completes when a thread has terminated executing.
int	end_simulation_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL))
			return (1);
	}
	pthread_join(table->death, NULL);
	return (0);
}
