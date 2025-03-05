/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 18:48:36 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/15 18:48:36 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	error_bool(char *message)
{
	printf(RED "Error: %s\n" RST, message);
	return (false);
}

void	print_activity(t_status status, t_philo *philo)
{
	long	time_stamp;

	pthread_mutex_lock(&philo->table->write_mutex);
	time_stamp = get_time(MILLISECOND) - philo->table->start_simulation;
	if ((status == TAKEN_FIRST_FORK || status == TAKEN_SEC_FORK) && \
		!dinner_finished(philo->table))
		printf(W"%ld"RST" %i has taken a fork\n", time_stamp, philo->philo_id);
	else if (status == EATING && !dinner_finished(philo->table))
		printf(GR"%ld"RST" %i is eating\n", time_stamp, philo->philo_id);
	else if (status == SLEEPING && !dinner_finished(philo->table))
		printf(W"%ld"RST" %i is sleeping\n", time_stamp, philo->philo_id);
	else if (status == THINKING && !dinner_finished(philo->table))
		printf(W"%ld"RST" %i is thinking\n", time_stamp, philo->philo_id);
	else if (status == DIED)
		printf(RED"%ld"RST" %i died\n", time_stamp, philo->philo_id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
