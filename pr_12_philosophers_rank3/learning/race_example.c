#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h> // intptr_t
#include <unistd.h> // usleep();

// single global var
int accum = 0;

void *square(void *x)
{
	int xi = *(int *)x;
	usleep(500); // microseconds, creates the visible race: diff results
    accum += xi * xi;
	free(x);
    return NULL; // nth to return, prevent warning
}
/**
 * to run main 40 times:
 * for i in {1..40}; do ./a.out; done
 * cc -Wall -Werror -Wall race_example.c && ./a.out 
 * cc -Wall -Werror -Wextra -pthread race_example.c -o race_example
 */
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
    {
        void *res;
		//On success, pthread_join() returns 0; on error, it returns an error number.
        pthread_join(ths[i], &res); // blocking operation
    }
    printf("accum = %d\n", accum);
    return (0);
}