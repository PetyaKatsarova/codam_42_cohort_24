/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:56:28 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/09 16:07:29 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

/**
 * Sleeps for ms but wakes up every 500μs to check if a philosopher
 * has died, exiting early if so.
 */
int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead)
		return (pthread_mutex_unlock(&data->dead_mutex), 1);
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

/**
 * If not dying soon, sleeps for 1ms
 */
static	void	give_priority(t_data *data, t_philo *ph)
{
	unsigned long	now;
	unsigned long	time_left;

	pthread_mutex_lock(&ph->update_last_meal_mutex);
	now = get_time_ms();
	time_left = data->args.time_to_die - (now - ph->last_meal);
	pthread_mutex_unlock(&ph->update_last_meal_mutex);
	if (time_left > data->args.time_to_die / 10)
		my_usleep(1000);
}

void	*philo_routine(void *philo)
{
	t_philo		*ph;
	t_data		*data;

	ph = (t_philo *)philo;
	data = ph->data;
	pthread_mutex_lock(&ph->data->synch_mutex);
	pthread_mutex_unlock(&ph->data->synch_mutex);
	if (ph->id % 2)
		my_usleep(1000);
	while (!is_dead(data))
	{
		thinking(ph);
		give_priority(data, ph);
		eating(ph, data);
		sleeping(ph, data);
	}
	return (NULL);
}
