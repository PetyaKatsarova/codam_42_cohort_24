#include "include/philo.h"

static unsigned long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}

static void	smart_sleep(unsigned long ms)
{
	unsigned long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100); // sleep in short bursts to stay responsive
}

static void print_state(char *msg, t_philo *ph)
{
    t_data *data = ph->data;
    unsigned long time = get_time_ms() - data->start_time;
    pthread_mutex_lock(&data->print_mutex);
    if (!data->dead)
        printf("%lu %d %s\n", time, ph->id, msg); // todo: replace with write: for not overwriting like in minishell...
    pthread_mutex_unlock(&data->print_mutex);
}

void *philo_routine(void *ptr)
{
    t_philo *ph = (t_philo *)ptr;
    t_data  *data = ph->data;

    if (ph->id % 2 == 0)
        usleep(1000); // sleep 1 s?
    while (!data->dead)
    {
        print_state("is thinking", ph);
        pthread_mutex_lock(ph->left_fork);
        print_state("has taken left fork", ph);
        pthread_mutex_lock(ph->right_fork);
        print_state("has taken right fork", ph);
        ph->last_meal = get_time_ms();
        print_state("is eating", ph);
        smart_sleep(data->args.time_to_eat);
        ph->meals_eaten++;
        pthread_mutex_unlock(ph->right_fork);
        pthread_mutex_unlock(ph->left_fork);
        print_state("is sleeping", ph);
        smart_sleep(data->args.time_to_sleep);
    }
    return (NULL);
}
