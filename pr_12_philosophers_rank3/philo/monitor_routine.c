/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_routine.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:30:39 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/05 19:55:33 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

//static int	all_philos_ate_enough(t_data *data)
//{
//	int	i;

//	if (data->args.num_if_times_to_eat < 0)
//		return (0);
//	i = 0;
//	while (i < data->args.ph_count)
//	{
//		pthread_mutex_lock(&data->philos[i].meals_eaten_mutex);
//		if (data->philos[i].meals_eaten < data->args.num_if_times_to_eat)
//		{
//			pthread_mutex_unlock(&data->philos[i].meals_eaten_mutex);
//			return (0);
//		}
//		pthread_mutex_unlock(&data->philos[i].meals_eaten_mutex);
//		i++;
//	}
//	return (1);
//}

//static int	some_helper(t_data *data)
//{
//	int				i;
//	unsigned long	now;

//	i = 0;
//	while (i < data->args.ph_count)
//	{
//		pthread_mutex_lock(&data->philos[i].meals_eaten_mutex);
//		now = get_time_ms();
//		if ((now - data->philos[i].last_meal) > data->args.time_to_die)
//		{
//			pthread_mutex_lock(&data->print_mutex);
//			pthread_mutex_lock(&data->dead_mutex);
//			if (!data->dead)
//				print_death(data, now, i);
//			pthread_mutex_unlock(&data->dead_mutex);
//			pthread_mutex_unlock(&data->print_mutex);
//			pthread_mutex_unlock(&data->philos[i].meals_eaten_mutex);
//			return (1);
//		}
//		pthread_mutex_unlock(&data->philos[i++].meals_eaten_mutex);
//	}
//	return (0);
//}

//static void	*check_monitor(t_data *data)
//{
//	if (some_helper(data))
//		return (NULL);
//	if (all_philos_ate_enough(data))
//	{
//		pthread_mutex_lock(&data->dead_mutex);
//		data->dead = 1;
//		pthread_mutex_unlock(&data->dead_mutex);
//		return (NULL);
//	}
//	return ((void *)1);
//}

//void	*monitor_routine(void *arg)
//{
//	t_data	*data;

//	data = (t_data *)arg;
//	while (1)
//	{
//		pthread_mutex_lock(&data->dead_mutex);
//		if (data->dead)
//		{
//			pthread_mutex_unlock(&data->dead_mutex);
//			break ;
//		}
//		pthread_mutex_unlock(&data->dead_mutex);
//		if (check_monitor(data) == NULL)
//			return (NULL);
//		usleep(500);
//	}
//	return (NULL);
//}





static int	monitor_loop(t_data *d)
{
	int	i = 0, full = 0;
	while (i < d->args.ph_count)
	{
		pthread_mutex_lock(&d->philos[i].meals_eaten_mutex);
		if (get_time_ms() - d->philos[i].last_meal > d->args.time_to_die)
		{
			pthread_mutex_lock(&d->print_mutex);
			pthread_mutex_lock(&d->dead_mutex);
			if (!d->dead)
			{
				print_death(d, get_time_ms(), i);
				d->dead = 1;
			}
			pthread_mutex_unlock(&d->dead_mutex);
			pthread_mutex_unlock(&d->print_mutex);
			pthread_mutex_unlock(&d->philos[i].meals_eaten_mutex);
			return (1);
		}
		if (d->args.num_if_times_to_eat >= 0 &&
			d->philos[i].meals_eaten >= d->args.num_if_times_to_eat)
			full++;
		pthread_mutex_unlock(&d->philos[i++].meals_eaten_mutex);
	}
	if (d->args.num_if_times_to_eat >= 0 && full == d->args.ph_count)
		return (pthread_mutex_lock(&d->dead_mutex), d->dead = 1,
			pthread_mutex_unlock(&d->dead_mutex), 1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*d = arg;
	while (1)
	{
		pthread_mutex_lock(&d->dead_mutex);
		if (d->dead)
			return (pthread_mutex_unlock(&d->dead_mutex), NULL);
		pthread_mutex_unlock(&d->dead_mutex);
		if (monitor_loop(d))
			break ;
		usleep(1000);
	}
	return (NULL);
}


