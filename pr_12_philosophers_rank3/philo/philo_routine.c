/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:56:28 by pekatsar          #+#    #+#             */
/*   Updated: 2025/06/04 09:47:09 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

/**
 * Sleeps for ms but wakes up every 500μs to check if a philosopher
 * has died, exiting early if so.
 */
static void	smart_sleep(unsigned long ms, t_data *data)
{
	unsigned long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		usleep(500);
	}
}

/**
 * Locks/unlocks print && dead_mutexes, checking if not dead, print the msg
 */
// static void	print_state(char *msg, t_philo *ph)
// {
// 	t_data			*data;
// 	unsigned long	curr_time;

// 	data = ph->data;
// 	curr_time = get_time_ms() - data->start_time;
// 	pthread_mutex_lock(&data->print_mutex);
// 	pthread_mutex_lock(&data->dead_mutex);
// 	if (!data->dead)
// 		printf("%lu %d %s\n", curr_time, ph->id, msg);
// 	pthread_mutex_unlock(&data->dead_mutex);
// 	pthread_mutex_unlock(&data->print_mutex);
// }

static int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead)
		return (pthread_mutex_unlock(&data->dead_mutex), 1);
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

static void	eat_sleep(t_philo *ph, t_fork *first, t_fork *second,
		t_data *data)
{
	pthread_mutex_lock(&first->mutex);
	print_state("has taken a fork", ph);
	pthread_mutex_lock(&second->mutex);
	print_state("has taken a fork", ph);
	pthread_mutex_lock(&ph->meals_eaten_mutex);
	ph->last_meal = get_time_ms();
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->meals_eaten_mutex);
	print_state("is eating", ph);
	smart_sleep(data->args.time_to_eat, data);
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
	print_state("is sleeping", ph);
	smart_sleep(data->args.time_to_sleep, data);
	if (ph->id % 2 == 0)
		usleep(1000);
	else
		usleep(500);
	// usleep(data->args.time_to_eat * 0.5); // eats 7 times if asked but 
	// 200 philos die, can have less
}

void	*philo_routine(void *philo)
{
	t_philo		*ph;
	t_data		*data;
	t_fork		*first;
	t_fork		*second;

	ph = (t_philo *)philo;
	data = ph->data;
	usleep(ph->id * 10);
	while (1)
	{
		if (is_dead(data))
			break ;
		print_state("is thinking", ph);
		usleep(500);
		first = ph->left_fork;
		second = ph->right_fork;
		if (first > second)
		{
			first = ph->right_fork;
			second = ph->left_fork;
		}
		eat_sleep(ph, first, second, data);
	}
	return (NULL);
}
