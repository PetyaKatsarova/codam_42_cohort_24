#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h> // intptr_t

// single global var
int accum = 0;

void *square(void *x)
{
    intptr_t xi = (intptr_t)x;
    accum += xi * xi;
    return NULL; // nth to return, prevent warning
}
/**
 * to run main 40 times:
 * for i in {1..40}; do ./a.out; done
 */
int main()
{
    pthread_t ths[20];
    for (int i = 0; i < 20; i++)
    {
        pthread_create(&ths[i], NULL, square, (void *)(intptr_t)(i + 1));
    }
    for (int i = 0; i < 20; i++)
    {
        void *res;
        pthread_join(ths[i], &res); // blocking operation
    }
    printf("accum = %d\n", accum);
    return (0);
}