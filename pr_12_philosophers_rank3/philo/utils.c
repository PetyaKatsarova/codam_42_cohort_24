/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:36:24 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/03 17:58:31 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

unsigned long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}
