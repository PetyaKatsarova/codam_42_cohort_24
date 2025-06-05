/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo_action.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/22 22:00:15 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/27 15:21:06 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>
#include <unistd.h>

static void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->forks[PHILO_FORK_RIGHT]);
	logger_log(p, MESSAGE_FORK);
	pthread_mutex_lock(p->forks[PHILO_FORK_LEFT]);
	logger_log(p, MESSAGE_FORK);
	philo_update_eat_time(p);
	logger_log(p, MESSAGE_EAT);
	sleep_ms(p->meta->args.time_to_eat);
	pthread_mutex_unlock(p->forks[PHILO_FORK_RIGHT]);
	pthread_mutex_unlock(p->forks[PHILO_FORK_LEFT]);
	philo_update_eat_count(p);
}

static void	philo_sleep(t_philo *p)
{
	logger_log(p, MESSAGE_SLEEP);
	sleep_ms(p->meta->args.time_to_sleep);
}

static void	philo_think(t_philo *p)
{
	logger_log(p, MESSAGE_THINK);
	if (p->id % 2)
		sleep_ms(1);
}

void	*philo_main(void *arg)
{
	t_philo			*p;

	p = arg;
	pthread_mutex_lock(&p->meta->mutex_sync);
	pthread_mutex_unlock(&p->meta->mutex_sync);
	if (p->meta->philo_failed)
		return (NULL);
	if (p->id % 2)
		sleep_ms(1);
	if (p->meta->args.philo_count == 1)
	{
		logger_log(p, MESSAGE_FORK);
		return (p);
	}
	while (!sim_get_stop(p->meta))
	{
		philo_think(p);
		philo_eat(p);
		philo_sleep(p);
	}
	return (p);
}
