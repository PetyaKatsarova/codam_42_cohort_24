#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for usleep)()

void *roll_dice()
{
    int *res = malloc(sizeof(int));
    *res = (rand() % 6) + 1;
    printf("Thread adress: %p\n", res);
    return ((void *) res);
}

 /**
  *  cc -Wall -Werror -Wextra -pthread thread_returns.c && ./a.out
  *  for i in {1..40}; do ./a.out; done
  */
int main()
{
    int *res;
    srand(time(NULL));
    pthread_t th;

    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
        return (1);
    if (pthread_join(th, (void **) &res) != 0)
        return (2);
    printf("Respo address: %p\n", res);
    printf("Res: %d\n", *res);
    free(res);
    return (0);
}

