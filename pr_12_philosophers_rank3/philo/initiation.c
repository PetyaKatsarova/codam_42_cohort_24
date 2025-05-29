#include "include/philo.h"

/**
 * Checks if received 5 or 6 args and valid int or unsigned long.
 * Returns 0 if correct input, else 1
 */
static int	parser_checker(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (ft_atoi(argv[1]) == -1)
		return (1);
	if (ft_atoul(argv[2]) == 0)
		return (1);
	if (ft_atoul(argv[3]) == 0)
		return (1);
	if (ft_atoul(argv[4]) == 0)
		return (1);
	if (argc == 6 && ft_atoi(argv[5]) == -1)
		return (1);
	return (0);
}

int init_args(t_argv *args_struct, int argc, char **argv)
{
    if (parser_checker(argc, argv) == 1)
    {
        printf("Naughty, naughty... u can give only positive nums starting from 1 and the format is:\n*number_philos *time_to_die *time_to_eat *time_to_sleep [*times_to_eat_optional]\n");
        return (1);
    }
    args_struct->ph_count = ft_atoi(argv[1]);
    args_struct->time_to_die = ft_atoul(argv[2]);
    args_struct->time_to_eat = ft_atoul(argv[3]);
    args_struct->time_to_sleep = ft_atoul(argv[4]);
    if (argc == 6)
        args_struct->num_if_times_to_eat = ft_atoi(argv[5]);
    else
        args_struct->num_if_times_to_eat = -1;
    return (0);
}
/**
 * Inits t_data mutexes(forks, dead and print_mutex)
 * Create thread per philo with philo_routine
 * Malloc's *forks and *philos
 */
int init_data(t_argv *argv_struct, t_data *data)
{
    int i;
    
    data->args = *argv_struct;
    data->dead = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * argv_struct->ph_count);
    // todo: protect the malloc: if fails..
    data->philos = malloc(sizeof(t_philo) * argv_struct->ph_count);
    // todo: protect malloc again
    pthread_mutex_init(&data->print_mutex, NULL); // todo: print_mutex : printing funcs
	pthread_mutex_init(&data->dead_mutex, NULL); // todo: same
    for (i = 0; i < argv_struct->ph_count; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    i = 0;
    while (i < argv_struct->ph_count)
    {
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % argv_struct->ph_count];
        data->philos[i].data = data; // todo: do i need it?
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal = 0;
		pthread_mutex_init(&data->philos[i].meals_eaten_mutex, NULL);
        i++;
    }

    return (0);
}
