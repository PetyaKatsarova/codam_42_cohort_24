/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/27 14:30:56 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/27 19:34:35 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "include/philo.h"

static void clean_up(t_data *data)
{
    for (int i = 0; i < data->args.ph_count; i++)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
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
	argv_t		args;
	pthread_t	monitor;
	int			i;

	if (init_args(&args, argc, argv))
		return (1); // todo: handle
	if (init_data(&args, &data))
		return (printf("Initialization failed\n"),1); // todo: handle
	data.start_time = get_time_ms();
	for (i = 0; i < args.ph_count; i++)
		data.philos[i].last_meal = data.start_time;
	for (i = 0; i < args.ph_count; i++)
		pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);
	pthread_create(&monitor, NULL, monitor_routine, &data);
	pthread_join(monitor, NULL); //  wait for monitor first
	i = 0;
	while (i < args.ph_count)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	clean_up(&data);
	return (0);
}
