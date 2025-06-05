/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/21 16:34:12 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/26 23:55:26 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>

static void	philo_swap_forks(t_philo *p)
{
	pthread_mutex_t	*tmp;

	tmp = p->forks[PHILO_FORK_LEFT];
	p->forks[PHILO_FORK_LEFT] = p->forks[PHILO_FORK_RIGHT];
	p->forks[PHILO_FORK_RIGHT] = tmp;
}

static t_philo	*philo_init(t_philo *p, t_meta *meta, uint32_t i)
{
	p->meta = meta;
	p->id = i + 1;
	p->forks[PHILO_FORK_LEFT] = &meta->forks[i];
	p->forks[PHILO_FORK_RIGHT] = &meta->forks[(i + 1) % meta->args.philo_count];
	if (p->id % 2)
		philo_swap_forks(p);
	if (pthread_mutex_init(&p->mutex_eat_time, NULL))
		return (NULL);
	if (pthread_mutex_init(&p->mutex_eat_count, NULL))
	{
		pthread_mutex_destroy(&p->mutex_eat_time);
		return (NULL);
	}
	if (pthread_create(&p->thread, NULL, philo_main, p))
	{
		pthread_mutex_destroy(&p->mutex_eat_time);
		pthread_mutex_destroy(&p->mutex_eat_count);
		return (NULL);
	}
	return (p);
}

static void	premature_fail_philos(t_meta *meta, size_t len)
{
	meta->philo_failed = true;
	pthread_mutex_unlock(&meta->mutex_sync);
	free_philos(meta->philos, len);
}

int	philos_init(t_meta *meta, uint32_t count)
{
	int32_t	i;

	i = 0;
	meta->philos = ft_calloc(sizeof(t_philo), count);
	if (!meta->philos)
		return (0);
	while (i < meta->args.philo_count)
	{
		if (!philo_init(&meta->philos[i], meta, i))
		{
			premature_fail_philos(meta, i);
			return (1);
		}
		i++;
	}
	return (0);
}
