/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/27 14:30:56 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/05 19:33:24 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static	int	total_init(t_data *data, t_argv *args, char **argv, int argc)
{
	if (init_args(args, argc, argv))
		return (1);
	if (args->ph_count == 1)
		return (printf("0 1 died\n"), 1);
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
	// lock start mutex
	pthread_mutex_init(&data.synch_mutex, NULL);
	pthread_mutex_lock(&data.synch_mutex);
	while (i < args.ph_count)
	{
		data.philos[i].last_meal = data.start_time;
		pthread_create(&data.philos[i].thread, NULL,
			philo_routine, &data.philos[i]);
			i++;
	}
	// unlock start mutex
	pthread_mutex_unlock(&data.synch_mutex);
	// destroy
	pthread_create(&monitor, NULL, monitor_routine, &data);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < args.ph_count)
		pthread_join(data.philos[i++].thread, NULL);
	return (cleanup_all(&data), 0);
}
