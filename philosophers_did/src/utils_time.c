/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_time.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 00:15:16 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/22 00:15:16 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Blocks each philo until all philos are ready.
void	wait_for_all_philos(t_table *table)
{
	while (!read_bool(&table->table_mutex, &table->philos_ready))
		;
}

// Converts time from seconds to the requested unit: 
// tv_sec gives seconds. * 1000 to get milli, * million for micros.
// tv_usec gives micros. / 1000 to get milli.
// MICROSECOND is used for fine-grained timing (small delays, precise syncing).
// MILLISECOND is for larger intervals (meal durations), optimizing performance.
long	get_time(t_time unit)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("Failed retrieving gettimeofday\n");
		return (-1);
	}
	if (unit == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	if (unit == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
	{
		printf("Gettimeofday failed\n");
		return (-1);
	}
}

// Delays philo's actions to prevent deadlocks and overlapping actions.
// Even num: Even's wait 30 ms to spread out actions.
// Odd num: Odd's think first to balance timing and avoid everyone grabbing
// forks at once. This reduces repeated conflicts and ensures fairer turns.
void	resync_thinking(t_philo *philo)
{
	if (philo->table->num_of_philos % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			hyper_sleep(30000, philo->table);
	}
	else
	{
		if (philo->philo_id % 2 != 0)
			think(philo, false);
	}
}

// A precise sleep function that combines usleep and a spinlock 
// to wait for a specified duration, while periodically checking 
// if the simulation has ended. Ensures accurate timing even for small delays.
void	hyper_sleep(long micro_sec, t_table *table)
{
	long	start;
	long	passed_time;
	long	sleep_left;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < micro_sec)
	{
		if (dinner_finished(table))
			break ;
		passed_time = get_time(MICROSECOND) - start;
		sleep_left = micro_sec - passed_time;
		if (sleep_left > 1000)
		{
			usleep(200);
			if (dinner_finished(table))
				break ;
		}
		else
		{
			while (get_time(MICROSECOND) - start < micro_sec && \
				!dinner_finished(table))
				;
		}
	}
}
