/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   free.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/28 18:52:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/25 16:14:32 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

void	free_philos(t_philo *philos, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(philos);
}

int	free_mutexes(pthread_mutex_t *arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&arr[i]);
		i++;
	}
	return (0);
}
