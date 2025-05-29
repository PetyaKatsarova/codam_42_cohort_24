/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:01:23 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/29 10:08:16 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

/**
 * Checks meals_eaten if still left times to eat
 * Returns 1 if still need to eat, 0 if times to eat is reached
 * todo: but if we dont have times to eat: return 0? 
 */
static int all_philos_ate_enough(t_data *data)
{
	if (data->args.num_if_times_to_eat < 0)
		return 0; // no limit
	for (int i = 0; i < data->args.ph_count; i++)
	{
		pthread_mutex_lock(&data->philos[i].meals_eaten_mutex);
		if (data->philos[i].meals_eaten < data->args.num_if_times_to_eat)
		{
			pthread_mutex_unlock(&data->philos[i].meals_eaten_mutex);
			return 0;
		}
		pthread_mutex_unlock(&data->philos[i].meals_eaten_mutex);
	}
	return 1;
}
// !! TODO: LIMIT FOR MEALS TO EAT
void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;

	while (1)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&data->dead_mutex);

		for (int i = 0; i < data->args.ph_count; i++)
		{
			pthread_mutex_lock(&data->philos[i].meals_eaten_mutex);

			unsigned long now = get_time_ms();
			if ((now - data->philos[i].last_meal) > data->args.time_to_die)
			{
				pthread_mutex_lock(&data->print_mutex);
				pthread_mutex_lock(&data->dead_mutex);
				if (!data->dead)
				{
					printf("%lu %d died\n", now - data->start_time, data->philos[i].id);
					data->dead = 1;
				}
				pthread_mutex_unlock(&data->dead_mutex);
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_unlock(&data->philos[i].meals_eaten_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&data->philos[i].meals_eaten_mutex);
		}

		if (all_philos_ate_enough(data))
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return NULL;
		}

		usleep(1000); // 1 ms to prevent cpu overuse, gives tim eto os to run toehr threads and still detectes death almost immidately, can try 500: tweak
	}
	return NULL;
}

