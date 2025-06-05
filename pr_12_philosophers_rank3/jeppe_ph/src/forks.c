/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   forks.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/26 18:17:25 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/26 15:53:58 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

int8_t	forks_init(t_meta *meta, size_t count)
{
	uint32_t	i;

	i = 0;
	meta->forks = ft_calloc(sizeof(pthread_mutex_t), count);
	if (!meta->forks)
		return (1);
	while (i < count)
	{
		if (pthread_mutex_init(&meta->forks[i], NULL))
		{
			free_mutexes(meta->forks, i);
			free(meta->forks);
			return (1);
		}
		i++;
	}
	return (0);
}
