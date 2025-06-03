/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:56:28 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/03 18:27:31 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

/**
 * Sleeps for ms milliseconds but wakes up every 500μs to check if a philosopher
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
static void	print_state(char *msg, t_philo *ph)
{
	t_data			*data;
	unsigned long	curr_time;

	data = ph->data;
	curr_time = get_time_ms() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->dead_mutex);
	if (!data->dead)
		printf("%lu %d %s\n", curr_time, ph->id, msg);
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_unlock(&data->print_mutex);
}

static int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead)
		return (pthread_mutex_unlock(&data->dead_mutex), 1);
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

static void	helper_routine(t_philo *ph, t_fork *first, t_fork *second,
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
		if (check_death(data))
			break ;
		print_state("is thinking", ph);
		usleep(500); // solves death: 4 410 200 200
		first = ph->left_fork;
		second = ph->right_fork;
		if (first > second)
		{
			first = ph->right_fork;
			second = ph->left_fork;
		}
		helper_routine(ph, first, second, data);
	}
	return (NULL);
}
