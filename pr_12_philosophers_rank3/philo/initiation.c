#include "include/philo.h"

// todo: should it be static?
int init_args(argv_t *args_struct, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("Usage: ./philo ph_count t_die t_eat t_sleep [n_eat]\n");
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
    pthread_mutex_init(&data->print_mutex, NULL);

    for (i = 0; i < argv_struct->ph_count; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    i = 0;
    while ( i < argv_struct->ph_count)
    {
        data->philos[i].id = i + 1;
        data->philos->left_fork = &data->forks[i];
        data->philos->right_fork = &data->forks[(i + 1) % argv_struct->ph_count];
        data->philos[i].data = data;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal = 0;
        pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);

        i++;
    }
    return (0);
}
