/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:30:56 by pekatsar          #+#    #+#             */
/*   Updated: 2025/06/07 11:34:55 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static	int	total_init(t_data *data, t_argv *args, char **argv, int argc)
{
	unsigned long	curr_time;

	curr_time = 0;
	if (init_args(args, argc, argv))
		return (1);
	if (args->ph_count == 1)
	{
		curr_time = get_time_ms();
		return (printf("%lu 1 died\n", curr_time), 1);
	}
	if (init_data(args, data))
		return (printf("Data initialization failed\n"), cleanup_all(data), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_argv		args;
	pthread_t	monitor;
	int			i;

	if (total_init(&data, &args, argv, argc) == 1)
		return (1);
	data.start_time = get_time_ms();
	i = 0;
	pthread_mutex_init(&data.synch_mutex, NULL);
	pthread_mutex_lock(&data.synch_mutex);
	while (i < args.ph_count)
	{
		data.philos[i].last_meal = data.start_time;
		pthread_create(&data.philos[i].thread, NULL,
			philo_routine, &data.philos[i]);
			i++;
	}
	pthread_mutex_unlock(&data.synch_mutex);
	pthread_create(&monitor, NULL, monitor_routine, &data);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < args.ph_count)
		pthread_join(data.philos[i++].thread, NULL);
	return (cleanup_all(&data), 0);
}
