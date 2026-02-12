/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:36:24 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/09 11:55:03 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

unsigned long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}

// custom sleep: now in milisec 
void	milli_sleep(unsigned long ms)
{
	unsigned long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
		usleep(100);
}

/*
** my_usleep(us): sleep approximately 'us' microseconds
*/
void	my_usleep(unsigned long us)
{
	struct timeval	start_tv;
	struct timeval	curr_tv;
	unsigned long	start;
	unsigned long	curr;

	gettimeofday(&start_tv, NULL);
	start = start_tv.tv_sec * 1000000UL + start_tv.tv_usec;
	while (1)
	{
		gettimeofday(&curr_tv, NULL);
		curr = curr_tv.tv_sec * 1000000UL + curr_tv.tv_usec;
		if (curr - start >= us)
			break ;
		usleep(50);
	}
}
