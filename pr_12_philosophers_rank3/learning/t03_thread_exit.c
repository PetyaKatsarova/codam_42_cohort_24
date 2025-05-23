/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t03_thread_exit.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/23 13:08:12 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/23 13:25:38 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h> // intptr_t
#include <unistd.h> // usleep();

void *roll_dice()
{
	int *result = malloc(sizeof(int));
	*result = (rand() % 6) + 1;
	printf("Thread res: %d\n", *result);
	sleep(2);
	pthread_exit((void *) result);
}

/**
 * cc -Wall -Werror -Wextra -pthread t03_thread_exit.c  && ./a.out
  * for i in {1..40}; do ./a.out; done
 */
int main ()
{
	int *res;
	srand(time(NULL));
	pthread_t th;

	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return (1);
		/**
		 * usefull when you want to exit main and leave threads running on the backgground, but res is not freed!
		 */
	pthread_exit(0); // wait for all threads to exec end exits on join, no last printf
	if (pthread_join(th, (void **)&res) != 0)
		return (2);
	printf("Res is:     %d\n", *res);
	free(res);
	return (0);
}