/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:30:56 by pekatsar          #+#    #+#             */
/*   Updated: 2025/06/03 10:54:37 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include/philo.h"

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
		return (printf("Data initialization failed\n"), cleanup_all(&data));
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
	return (cleanup_all(&data), 0);
}
