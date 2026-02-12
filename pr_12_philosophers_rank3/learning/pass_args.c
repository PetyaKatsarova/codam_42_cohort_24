#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for usleep)()

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void *routine(void *arg)
{
    sleep(1);
    int i = *(int *)arg;
    printf("i: %d and prime: %d\n", i, primes[i]);
    free(arg);
    return (NULL);
}

 /**
  *  cc -Wall -Werror -Wextra -pthread pass_args.c && ./a.out
  *  for i in {1..40}; do ./a.out; done
  */
int main()
{
    pthread_t th[10];
    int i;

    for (i = 0; i < 10; i++)
    {
        int *bla = malloc(sizeof(int));
        *bla = i;
        if (pthread_create(&th[i], NULL, &routine, bla) != 0)
        {
            perror("Failed to create thread\n");
        }
    }
    for (i = 0; i < 10; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread\n");
        }
    }
    return (0);
}