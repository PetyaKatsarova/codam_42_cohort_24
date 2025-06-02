#include "include/philo.h"

unsigned long	get_time_ms()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}

/**
 * 
 */
static void smart_sleep(unsigned long ms, t_data *data)
{
	unsigned long start = get_time_ms();
	while (get_time_ms() - start < ms)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		usleep(500); // shorter chunk sleep
	}
}

/**
 * Locks/unlocks print && dead_mutexes, checking if not dead, print the msg
 */
static void print_state(char *msg, t_philo *ph)
{
    t_data 		*data = ph->data; // just to make it cleaner
    unsigned	long curr_time = get_time_ms() - data->start_time;
    pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->dead_mutex);
	if (!data->dead)
		printf("%lu %d %s\n", curr_time, ph->id, msg);
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_unlock(&data->print_mutex);
}
/**
 * Lock 2 forks(imaginary resources) and inside add the set time for eating, unlock, can think(doesnt take time) and sleep(set time, can be parallel, no shared resources)
 */

void	*philo_routine(void *philo)
{
	t_philo			*ph = (t_philo *)philo;
	t_data			*data = ph->data;
	t_fork			*first;
	t_fork			*second;

	// avoid deadlock
	if (ph->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		print_state("is thinking", ph);
		// deadlock avoidance
		first = ph->left_fork;
		second = ph->right_fork;
		if (first > second)
		{
			first = ph->right_fork;
			second = ph->left_fork;
		}
		pthread_mutex_lock(&first->mutex);
		print_state("has taken a fork", ph);
		pthread_mutex_lock(&second->mutex);
		print_state("has taken a fork", ph);
		pthread_mutex_lock(&ph->meals_eaten_mutex); // or right_fork — both are locked already, so this is safe
		ph->last_meal = get_time_ms();
		ph->meals_eaten++;
		pthread_mutex_unlock(&ph->meals_eaten_mutex);
		//print_state("is eating", ph);
		char msg[64];
		snprintf(msg, sizeof(msg), "is eating (%d)", ph->meals_eaten); // rmv: only for testing: TODO
		print_state(msg, ph);
		smart_sleep(data->args.time_to_eat, data);
		pthread_mutex_unlock(&second->mutex);
		pthread_mutex_unlock(&first->mutex);

		print_state("is sleeping", ph);
		smart_sleep(data->args.time_to_sleep, data); // for 500 microseconds
		if (ph->id % 2 == 0)
			usleep(1000); // desync again before next cycle
	}
	return (NULL);
}


