/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   simulation.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/19 16:12:27 by jboeve        #+#    #+#                 */
/*   Updated: 2023/10/26 16:59:41 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>
#include <unistd.h>

static int	init_mutexes(pthread_mutex_t *arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&arr[i], NULL))
		{
			free_mutexes(arr, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	sim_start(t_meta *meta)
{
	if (init_mutexes(&meta->mutex_log, 3))
		return (0);
	pthread_mutex_lock(&meta->mutex_sync);
	if (forks_init(meta, meta->args.philo_count))
	{
		pthread_mutex_unlock(&meta->mutex_sync);
		free_mutexes(&meta->mutex_log, 3);
		return (0);
	}
	if (philos_init(meta, meta->args.philo_count))
	{
		pthread_mutex_unlock(&meta->mutex_sync);
		free_mutexes(&meta->mutex_log, 3);
		free_mutexes(meta->forks, meta->args.philo_count);
		free(meta->forks);
		return (0);
	}
	meta->log_start_time = get_time_ms();
	philo_init_eat_count_all(meta->philos, meta->args.philo_count);
	pthread_mutex_unlock(&meta->mutex_sync);
	usleep(1);
	monitor(meta);
	return (1);
}

void	sim_set_stop(t_meta *meta)
{
	pthread_mutex_lock(&meta->mutex_running);
	meta->sim_stop = true;
	pthread_mutex_unlock(&meta->mutex_running);
}

bool	sim_get_stop(t_meta *meta)
{
	bool	running;

	pthread_mutex_lock(&meta->mutex_running);
	running = meta->sim_stop;
	pthread_mutex_unlock(&meta->mutex_running);
	return (running);
}

int	sim_cleanup(t_meta *meta)
{
	free_philos(meta->philos, meta->args.philo_count);
	free_mutexes(&meta->mutex_log, 3);
	free_mutexes(meta->forks, meta->args.philo_count);
	free(meta->forks);
	return (1);
}
