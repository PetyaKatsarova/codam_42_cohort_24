#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for usleep)()

int accum = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *square(void *x)
{
    int bla = *(int *)x; // *() allocate the val of the poitner to the int bla, int *x would be alloc address
	usleep(500); // simulate delay
	pthread_mutex_lock(&lock);
	accum += bla * bla;
	pthread_mutex_unlock(&lock);
	free(x);
	return (NULL);
}
//cc -Wall -Werror -Wall -pthread mutex.c && ./a.out
//for i in {1..40}; do ./a.out; done

/**
 * pthread_join(ths[i], NULL);
Purpose: Waits for a specific thread to finish.
Ensures that all threads complete before main() exits.
Without it, main() might end early, and you’d miss results from unfinished threads.

All 20 threads start nearly at the same time.
Each thread tries to increment mails 1 million times.

But:
Only one thread at a time holds the lock (mutex).
The rest wait (blocked) at pthread_mutex_lock.
Parallel thread execution
Serial access to the shared variable mails due to the mutex
Net result: threads are competing, and taking turns to safely increment.
In short:
Threads run in parallel, but access to mails is sequential(One after another, in a specific order, not at the same time.).
 */

 int mails = 0;
 pthread_mutex_t mutex;

 void *routine()
 {
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
 }

 /**
  *  cc -Wall -Werror -Wextra -pthread mutex.c && ./a.out
  *  for i in {1..40}; do ./a.out; done
  */
int main()
{
	pthread_t ths[20];

	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 20; i++)
	{
		if (pthread_create(ths+i, NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	for (int i = 0; i < 20; i++)
	{
		if (pthread_join(ths[i], NULL) != 0)
			return (2);
		printf("Thread %d joined\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Num of mails: %d\n", mails);
	return (0);
}