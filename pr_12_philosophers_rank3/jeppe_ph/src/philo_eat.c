/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo_eat.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/20 00:25:12 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/26 16:59:29 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

int32_t	philo_get_eat_count(t_philo *p)
{
	int32_t	count;

	pthread_mutex_lock(&p->mutex_eat_count);
	count = p->eat_count;
	pthread_mutex_unlock(&p->mutex_eat_count);
	return (count);
}

void	philo_update_eat_time(t_philo *p)
{
	pthread_mutex_lock(&p->mutex_eat_time);
	p->last_eat_time = get_time_ms();
	pthread_mutex_unlock(&p->mutex_eat_time);
}

void	philo_update_eat_count(t_philo *p)
{
	pthread_mutex_lock(&p->mutex_eat_count);
	p->eat_count++;
	pthread_mutex_unlock(&p->mutex_eat_count);
}

void	philo_init_eat_count_all(t_philo *p, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		p[i].last_eat_time = get_time_ms();
		i++;
	}
}
