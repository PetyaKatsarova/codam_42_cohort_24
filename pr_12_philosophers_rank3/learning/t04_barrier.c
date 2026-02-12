/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t04_barrier.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/23 14:32:01 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/23 17:25:54 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // usleep();
#include <string.h>

pthread_barrier_t barrier;

void *routine()
{
	printf("Waiting at the barrier...\n");
	pthread_barrier_wait(&barrier);
	printf("We passed the barrier\n");
	return (NULL);
}

/**
 * cc -Wall -Werror -Wextra -pthread t04_barrier.c  && ./a.out
  * for i in {1..40}; do ./a.out; done
 */
int main ()
{
	int thread_count = 10;
	pthread_t th[thread_count];
	int i;

	pthread_barrier_init(&barrier, NULL, 3); // passes 3x3 threads, blocks waiting for 2 more to arrive... but we have 1 left
	for (i = 0; i < thread_count; i++)
	{
		if(pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Failed to create thread");
	}
	for (i = 0; i < thread_count; i++)
	{
		if(pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}
	pthread_barrier_destroy(&barrier);
	return (0);
}