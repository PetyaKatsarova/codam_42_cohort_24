/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 17:26:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/11/12 22:09:28 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function manages the eating process for a philosopher.
// It locks/takes both forks, logs the actions, updates meal time 
// and count, sleeps for the eating duration, and unlocks/drops
// the forks after handling possible meal limit.
static void	eat(t_philo *philo)
{
	if (toggle_lock_and_fork(LOCK, EATING, philo) == false)
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		return ;
	}
	update_long(&philo->monitor_mutex, &philo->last_meal_time, \
				get_time(MILLISECOND));
	philo->eaten_meals++;
	print_activity(EATING, philo);
	hyper_sleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limited_dinner == true && \
		philo->table->num_limit_meals == philo->eaten_meals)
	{
		pthread_mutex_lock(&philo->table->table_mutex);
		philo->table->num_of_full_philos++;
		pthread_mutex_unlock(&philo->table->table_mutex);
	}
	toggle_lock_and_fork(UNLOCK, EATING, philo);
}

// Calculates an fair think_time to keep philos in sync with eachother.
// This ensures a balanced cycle where each philo's actions stay consistent.
// It prevents situations where on philo skips thinking and immediately
// starts eating, while an actively thinking philo should be starting next.
void	think(t_philo *philo, bool in_dinner_cycle)
{
	long	eat_time;
	long	sleep_time;
	long	think_time;

	if (in_dinner_cycle == true)
		print_activity(THINKING, philo);
	if (philo->table->num_of_philos % 2 == 0)
		return ;
	eat_time = philo->table->time_to_eat;
	sleep_time = philo->table->time_to_sleep;
	think_time = eat_time * 2 - sleep_time;
	if (think_time < 0)
		think_time = 0;
	hyper_sleep(think_time * 0.40, philo->table);
}

// The actual eat, sleep, think cycle.
// Each philo waits untill all philos are ready, so they can sync up.
void	*philo_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_for_all_philos(philo->table);
	update_long(&philo->monitor_mutex, &philo->last_meal_time, \
				get_time(MILLISECOND));
	increase_active_threads(&philo->table->table_mutex, \
							&philo->table->active_threads);
	resync_thinking(philo);
	while (!dinner_finished(philo->table))
	{
		eat(philo);
		print_activity(SLEEPING, philo);
		hyper_sleep(philo->table->time_to_sleep, philo->table);
		if (dinner_finished(philo->table))
			break ;
		think(philo, true);
	}
	return (NULL);
}

// Starts the dining sim by creating a thread for each philo and
// a separate monitoring thread to check on their state.
// Sets the start time and updates if all philos are ready to start their
// meditation cycle.
int	begin_feast(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, \
							philo_cycle, &table->philos[i]) != 0)
			return (error_join_threads(table, i), 1);
	}
	if (pthread_create(&table->death, NULL, monitoring_death, table) != 0)
		return (error_join_threads(table, i), 1);
	table->start_simulation = get_time(MILLISECOND);
	if (table->start_simulation == -1)
		return (error_join_threads(table, i), 1);
	update_bool(&table->table_mutex, &table->philos_ready, true);
	return (end_simulation_threads(table));
}
