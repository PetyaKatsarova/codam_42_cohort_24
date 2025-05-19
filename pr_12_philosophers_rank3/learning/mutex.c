#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h> // intptr_t

int accum = 0;
pthread_mutex_t accum_mutex = PTHREAD_MUTEX_INITIALIZER;

void *square(void *x)
{
    intptr_t xi = (intptr_t)x;
    intptr_t temp = xi * xi;

    
}