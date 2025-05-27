#include "include/philo.h"

unsigned long	get_time_ms()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}

/**
 * Sleep in short bursts to stay responsive
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


static void print_state(char *msg, t_philo *ph)
{
    t_data 		*data = ph->data;
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

 /**
  * allows a philosopher to die, because the timing margin is too tight between when a philosopher finishes eating, sleeps, thinks, and then waits for forks again. The main problem is that sleep time + fork wait + scheduling delay > time_to_die.
  */
void	*philo_routine(void *ptr)
{
	t_philo			*ph = (t_philo *)ptr;
	t_data			*data = ph->data;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (ph->id % 2 == 0)
		usleep(data->args.time_to_eat * 1000 / 2);
		//usleep(1000); // reduce contention

	while (1)
	{
		// Check for death flag
		pthread_mutex_lock(&data->dead_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&data->dead_mutex);

		print_state("is thinking", ph);

		// Determine fork order (deadlock avoidance)
		first = ph->left_fork;
		second = ph->right_fork;
		if (first > second)
		{
			first = ph->right_fork;
			second = ph->left_fork;
		}

		// Lock forks
		pthread_mutex_lock(first);
		print_state("has taken a fork", ph);
		pthread_mutex_lock(second);
		print_state("has taken a fork", ph);

		// SAFELY update shared meal data (while holding forks)
		pthread_mutex_lock(&ph->meal_mutex); // or right_fork — both are locked already, so this is safe
		ph->last_meal = get_time_ms();
		ph->meals_eaten++;
		pthread_mutex_unlock(&ph->meal_mutex);

		//print_state("is eating", ph);


		char msg[64];
		snprintf(msg, sizeof(msg), "is eating (%d)", ph->meals_eaten);
		print_state(msg, ph);
		

		smart_sleep(data->args.time_to_eat, data);

		// Unlock forks
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);

		print_state("is sleeping", ph);
		smart_sleep(data->args.time_to_sleep, data);
		if (ph->id % 2 == 0)
			usleep(1000); // desync again before next cycle
	}
	return (NULL);
}


