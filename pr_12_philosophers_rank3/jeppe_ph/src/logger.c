/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   logger.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/13 16:41:06 by jboeve        #+#    #+#                 */
/*   Updated: 2023/10/26 16:58:53 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>

static const char	*get_log_msgs(t_message s)
{
	const char	*log_text[] = {
		"%lu %u has taken a fork\n",
		"%lu %u is eating\n",
		"%lu %u is sleeping\n",
		"%lu %u is thinking\n",
		"%lu %u died\n",
		"%lu %u test_msg\n",
	};

	return (log_text[s]);
}

void	logger_log(t_philo *p, t_message status)
{
	unsigned long	start_time;

	start_time = p->meta->log_start_time;
	pthread_mutex_lock(&p->meta->mutex_log);
	if (sim_get_stop(p->meta))
	{
		pthread_mutex_unlock(&p->meta->mutex_log);
		return ;
	}
	printf(get_log_msgs(status), get_time_ms() - start_time, p->id);
	pthread_mutex_unlock(&p->meta->mutex_log);
}
