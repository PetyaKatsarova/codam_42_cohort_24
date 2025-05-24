#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for usleep)()

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void *routine(void *arg) {
    int index = *(int *)arg;
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += primes[index + i];
    }
    *(int *)arg = sum; // val or arg
    return (arg); // memory address
}

 /**
  *  cc -Wall -Werror -Wextra -pthread simple_example.c && ./a.out
  *  for i in {1..40}; do ./a.out; done
  */
int main()
{
    pthread_t th[10];
    int i;

    for (i = 0; i < 2; i++)
    {
        int *bla = malloc(sizeof(int));
        *bla = i * 5;
        if (pthread_create(&th[i], NULL, &routine, bla) != 0)
            perror("Failed to create thread\n");
    }
    int globalSum = 0;
    for (i = 0; i < 2; i++)
    {
        int *r;
        if (pthread_join(th[i], (void **)&r) != 0)
            perror("Failed to join thread\n");
        globalSum += *r;
        free(r);
    }
    printf("Global sum: %d\n", globalSum); // 129
    return (0);
}