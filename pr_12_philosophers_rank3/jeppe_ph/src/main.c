/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/21 16:29:24 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/26 15:22:11 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

static const char	*get_pe_msgs(t_parse_error err)
{
	const char	*pe_msgs[] = {
		NULL,
		"usage: philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
		"Integer overflow!\n",
	};

	return (pe_msgs[err]);
}

int	philosophers(int argc, char *argv[])
{
	t_parse_error	err;
	t_meta			meta;

	ft_memset(&meta, 0, sizeof(t_meta));
	err = parse(&meta.args, argc, argv);
	if (err)
	{
		write(STDERR_FILENO, get_pe_msgs(err), ft_strlen(get_pe_msgs(err)));
		return (EXIT_FAILURE);
	}
	if (!sim_start(&meta))
		return (EXIT_FAILURE);
	sim_cleanup(&meta);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	return (philosophers(argc, argv));
}
