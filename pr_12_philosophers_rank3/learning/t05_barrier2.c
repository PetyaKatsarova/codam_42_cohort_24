/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t05_barrier2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/23 14:32:01 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/23 18:12:00 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // usleep();
#include <string.h>

#define THREAD_NUM 8

int diceVals[THREAD_NUM];
int status[THREAD_NUM] = {0};

pthread_barrier_t barrierRollDice;
pthread_barrier_t barrierCalculated;

void *rollDice(void *arg)
{
	int index = *(int *)arg; // = val of int pointer arg
	free(arg);
	while (1)
	{
		diceVals[index] = rand() % 32 + 1;
		pthread_barrier_wait(&barrierRollDice);
		pthread_barrier_wait(&barrierCalculated);
		if (status[index] == 1)
			printf("[%d rolled %d]I won\n", index, diceVals[index]);
		else
			printf("[%d rolled %d]I lost\n", index, diceVals[index]);
	}
	return (NULL);
}

/**
 * cc -Wall -Werror -Wextra -pthread t05_barrier2.c  && ./a.out
  * for i in {1..40}; do ./a.out; done
 */
int main ()
{
	srand(time(NULL));
	pthread_t th[THREAD_NUM];
	int i;

	pthread_barrier_init(&barrierRollDice, NULL, THREAD_NUM + 1);
	pthread_barrier_init(&barrierCalculated, NULL, THREAD_NUM + 1);
	for (i = 0; i < THREAD_NUM; i++)
	{
		int *bla = malloc(sizeof(int));
		*bla = i;
		if(pthread_create(&th[i], NULL, &rollDice, (void *) bla) != 0)
			perror("Failed to create thread");
	}
	while (1)
	{
		pthread_barrier_wait(&barrierRollDice); // wait here untill diceVals is populated from all threads
		int max = 0;
		for (i = 0; i < THREAD_NUM; i++)
		{
			if (diceVals[i] > max)
				max = diceVals[i];
		}

		for (i = 0; i < THREAD_NUM; i++)
			status[i] = (diceVals[i] == max) ? 1 : 0;
	
		printf("================== NEW ROUND ====================\n");
		pthread_barrier_wait(&barrierCalculated);
		sleep(1);
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		if(pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}
	pthread_barrier_destroy(&barrierRollDice);
	pthread_barrier_destroy(&barrierCalculated);
	return (0);
}