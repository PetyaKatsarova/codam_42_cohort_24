/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:30:56 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/28 21:53:10 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include/philo.h"

static void clean_up_data(t_data *data)
{
    for (int i = 0; i < data->args.ph_count; i++)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->dead_mutex);
    pthread_mutex_destroy(&data->print_mutex);

    free(data->forks);
    free(data->philos);
}
/**
 * TODO: MAKE SURE CHANGES IN PHILO.H STILL REBUILD PROJECT!!
 */
int	main(int argc, char **argv)
{
	t_data		data;
	t_argv		args;
	pthread_t	monitor;
	int			i;

	if (init_args(&args, argc, argv))
		return (1); // todo: handle
	if (init_data(&args, &data))
		return (printf("Initialization failed\n"),1); // todo: handle
	data.start_time = get_time_ms();
	for (i = 0; i < args.ph_count; i++)
	{
		data.philos[i].last_meal = data.start_time;
		pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);
	}

	pthread_create(&monitor, NULL, monitor_routine, &data);
	pthread_join(monitor, NULL); //  wait for monitor first
	i = 0;
	while (i < args.ph_count)
		pthread_join(data.philos[i++].thread, NULL);
	return (clean_up_data(&data), 0);
}
