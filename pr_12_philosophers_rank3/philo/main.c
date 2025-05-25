#include "include/philo.h"

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
