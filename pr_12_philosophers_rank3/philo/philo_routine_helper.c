#include "include/philo.h"

void thinking(t_philo *ph)
{
    print_state("is thinking", ph);
    if (ph->id % 2)
		my_usleep(500);
}

static void	smart_sleep(unsigned long ms, t_data *data)
{
	unsigned long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		my_usleep(500);
	}
}

static void	update_meals_count(t_philo *ph)
{
	pthread_mutex_lock(&ph->meals_eaten_mutex);
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->meals_eaten_mutex);
}

void eating(t_philo *ph, t_data *data)
{
	t_fork		*first;
	t_fork		*second;

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
	pthread_mutex_lock(&ph->update_last_meal_mutex);
	ph->last_meal = get_time_ms();
	pthread_mutex_unlock(&ph->update_last_meal_mutex);
	print_state("is eating", ph);
	smart_sleep(data->args.time_to_eat, data);
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
	// if (!is_dead(data))
  		update_meals_count(ph);
}

void sleeping(t_philo *ph, t_data *data)
{
    print_state("is sleeping", ph);
	smart_sleep(data->args.time_to_sleep, data);
}
