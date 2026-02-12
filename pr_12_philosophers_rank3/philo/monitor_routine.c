/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_routine.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:30:39 by pekatsar          #+#    #+#             */
/*   Updated: 2025/06/09 11:45:24 by pekatsar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static int	has_died(t_philo *ph)
{
	unsigned long	now;
	unsigned long	ttd;

	pthread_mutex_lock(&ph->update_last_meal_mutex);
	now = get_time_ms();
	ttd = ph->data->args.time_to_die;
	if (now - ph->last_meal >= ttd)
	{
		pthread_mutex_lock(&ph->data->print_mutex);
		pthread_mutex_lock(&ph->data->dead_mutex);
		if (!ph->data->dead)
		{
			print_death(ph->data, now, ph->id);
			ph->data->dead = 1;
		}
		pthread_mutex_unlock(&ph->data->dead_mutex);
		pthread_mutex_unlock(&ph->data->print_mutex);
		pthread_mutex_unlock(&ph->update_last_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->update_last_meal_mutex);
	return (0);
}

static int	monitor_loop(t_data *data)
{
	int		i;
	int		times_eaten;
	t_philo	*ph;

	i = 0;
	times_eaten = 0;
	while (i < data->args.ph_count)
	{
		ph = &data->philos[i];
		if (has_died(ph))
			return (1);
		pthread_mutex_lock(&ph->meals_eaten_mutex);
		if (data->args.num_if_times_to_eat >= 0
			&& ph->meals_eaten >= data->args.num_if_times_to_eat)
			times_eaten++;
		pthread_mutex_unlock(&ph->meals_eaten_mutex);
		i++;
	}
	if (data->args.num_if_times_to_eat >= 0
		&& times_eaten == data->args.ph_count)
	{
		pthread_mutex_lock(&data->dead_mutex);
		return (data->dead = 1, pthread_mutex_unlock(&data->dead_mutex), 1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = arg;
	while (1)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		if (monitor_loop(data))
			break ;
		usleep(500);
	}
	return (NULL);
}
