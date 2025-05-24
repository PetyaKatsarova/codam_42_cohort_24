#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void *fuel_filling() {
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 60;
        printf("filling fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_broadcast(&condFuel);
        sleep(1);
    }
    return (NULL);
}

void *car() {
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40)
    {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // equal to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel from another func
        // pthread_mutex_lock(&mutexFuel)
    }
    fuel -= 40;
    printf("Used 40l fuel. Left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
    return(NULL);
}

 /**
  *  cc -Wall -Werror -Wextra -pthread broadcasting.c && ./a.out
  *  for i in {1..40}; do ./a.out; done
  */
int main()
{
    pthread_t th[6];

    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 6; i++) {
        if (i == 4 || i == 5) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
                perror("Failed to create thread");
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0)
                perror("Failed to create thread");
        }
    }

    for (int i = 0; i < 6; i++) 
    {
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return (0);
}