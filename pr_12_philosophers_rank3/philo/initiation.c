#include "include/philo.h"

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

// todo: should it be static?
int init_args(argv_t *args_struct, int argc, char **argv)
{
    if (parser_checker(argc, argv) == 1)
    {
        printf("Naughty, naughty... u can give numbers between 1 and 10000 and the format is:\nnumber_philos time_to_die time_to_eat time_to_sleep [times_to_eat_optional]\n");
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

int init_data(argv_t *argv_struct, t_data *data)
{
    int i;
    
    data->args = *argv_struct;
    data->dead = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * argv_struct->ph_count);
    // todo: protect the malloc: if fails..
    data->philos = malloc(sizeof(t_philo) * argv_struct->ph_count);
    // todo: protect malloc again
    pthread_mutex_init(&data->print_mutex, NULL); // todo: print_mutex : printing funcs

    for (i = 0; i < argv_struct->ph_count; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    i = 0;
    while (i < argv_struct->ph_count)
    {
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % argv_struct->ph_count];
        data->philos[i].data = data;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal = 0;
        pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
        i++;
    }

    return (0);
}
