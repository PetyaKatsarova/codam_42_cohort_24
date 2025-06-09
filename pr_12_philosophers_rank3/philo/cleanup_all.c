/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup_all.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:34:53 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/09 11:42:03 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	cleanup_all(t_data *data)
{
	int	i;

	if (!data)
		return (1);
	if (data->philos)
	{
		i = 0;
		while (i < data->args.ph_count)
		{
			pthread_mutex_destroy(&data->philos[i++].meals_eaten_mutex);
			pthread_mutex_destroy(&data->philos[i++].update_last_meal_mutex);
		}
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->args.ph_count)
			pthread_mutex_destroy(&data->forks[i++].mutex);
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	return (pthread_mutex_destroy(&data->dead_mutex), 1);
}
