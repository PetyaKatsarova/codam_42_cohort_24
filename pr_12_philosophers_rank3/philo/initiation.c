/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:20:07 by pekatsar          #+#    #+#             */
/*   Updated: 2025/06/06 20:42:55 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static int	parser_checker(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (ft_atoi(argv[1]) == -1)
		return (1);
	if (ft_atoul(argv[2]) == 0)
		return (1);
	if (ft_atoul(argv[3]) == 0)
		return (1);
	if (ft_atoul(argv[4]) == 0)
		return (1);
	if (argc == 6 && ft_atoi(argv[5]) == -1)
		return (1);
	return (0);
}

int	init_args(t_argv *args_struct, int argc, char **argv)
{
	if (parser_checker(argc, argv) == 1)
	{
		printf("Naughty, naughty... u can give only positive");
		printf(" nums starting from 1 and the format is:\n");
		printf("* number_philos *time_to_die *time_to_eat");
		printf("* time_to_sleep [*times_to_eat_optional]\n");
		return (1);
	}
	args_struct->ph_count = ft_atoi(argv[1]);
	args_struct->time_to_die = ft_atoul(argv[2]);
	args_struct->time_to_eat = ft_atoul(argv[3]);
	args_struct->time_to_sleep = ft_atoul(argv[4]);
	if (argc == 6)
		args_struct->num_if_times_to_eat = ft_atoi(argv[5]);
	else
		args_struct->num_if_times_to_eat = -1;
	return (0);
}

static	void	init_phillos(t_data *data, int i, t_argv *argv_struct)
{
	data->philos[i].id = i + 1;
	data->philos[i].left_fork = &data->forks[i];
	data->philos[i].right_fork = &data->forks[(i + 1)
		% argv_struct->ph_count];
	data->philos[i].data = data;
	data->philos[i].meals_eaten = 0;
	data->philos[i].last_meal = 0;
	pthread_mutex_init(&data->philos[i].meals_eaten_mutex, NULL);
	pthread_mutex_init(&data->philos[i].update_last_meal_mutex, NULL);
}

int	init_data(t_argv *argv_struct, t_data *data)
{
	int				i;

	data->args = *argv_struct;
	data->dead = 0;
	data->forks = malloc(sizeof(t_fork) * argv_struct->ph_count);
	if (!data->forks)
		return (cleanup_all(data), 1);
	data->philos = malloc(sizeof(t_philo) * argv_struct->ph_count);
	if (!data->philos)
		return (cleanup_all(data), 1);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	i = 0;
	while (i < argv_struct->ph_count)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		data->forks[i++].taken = 0;
	}
	i = 0;
	while (i < argv_struct->ph_count)
	{
		init_phillos(data, i, argv_struct);
		i++;
	}
	return (0);
}
