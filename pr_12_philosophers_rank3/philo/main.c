#include "include/philo.h"

#include <stdio.h>
#include <stdlib.h>

int init_args(argv_t *args_struct, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("Usage: ./philo ph_count t_die t_eat t_sleep [n_eat]\n");
        return (1);
    }
    args_struct->ph_count = atoi(argv[1]);
    args_struct->time_to_die = strtoul(argv[2], NULL, 10);
    args_struct->time_to_eat = strtoul(argv[3], NULL, 10);
    args_struct->time_to_sleep = strtoul(argv[4], NULL, 10);
    if (argc == 6)
        args_struct->num_if_times_to_eat = atoi(argv[5]);
    else
        args_struct->num_if_times_to_eat = -1;
    return (0);
}

int main(int argc, char **argv)
{
    argv_t args;

    if (init_args(&args, argc, argv))
        return (1);

    printf("count: %d, die: %lu, eat: %lu, sleep: %lu, times_eat: %d\n",
           args.ph_count, args.time_to_die, args.time_to_eat,
           args.time_to_sleep, args.num_if_times_to_eat);

    return (0);
}
