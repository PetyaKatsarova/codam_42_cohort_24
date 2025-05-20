#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for usleep)()

int accum = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *square(void *x)
{
    int bla = *(int *)x;
	usleep(500); // simulate delay
	pthread_mutex_lock(&lock);
	accum += bla * bla;
	pthread_mutex_unlock(&lock);
	free(x);
	return (NULL);
}
//cc -Wall -Werror -Wall -pthread mutex.c && ./a.out
//for i in {1..40}; do ./a.out; done
int main()
{
	pthread_t ths[20];

	for (int i = 0; i < 20; i++)
	{
		int *val = malloc(sizeof(int));
		*val = i + 1;
		pthread_create(&ths[i], NULL, square, val);
	}
	for (int i = 0; i < 20; i++)
		pthread_join(ths[i], NULL);
	printf("accum = %d\n", accum);
	return (0);
}