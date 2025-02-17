/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   table_setting.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 17:46:49 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/15 17:46:49 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Used an even/odd order to prevent deadlocks, where even philos pick up
// their own left fork.Odd philos take their neighbor's fork. 
// This way, at least one philo can proceed.
static void	hand_out_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	num_of_philos;

	num_of_philos = philo->table->num_of_philos;
	if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % num_of_philos];
	}
	else
	{
		philo->first_fork = &forks[(philo_pos + 1) % num_of_philos];
		philo->second_fork = &forks[philo_pos];
	}
}

// The monitor_mutex protects each philos specific state information.
// This mutex prevents race conditions on those individual philos data elements.
static bool	inform_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_of_philos)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->eaten_meals = 0;
		philo->last_meal_time = 0;
		philo->table = table;
		if (pthread_mutex_init(&philo->monitor_mutex, NULL) != 0)
			return (free_table(table, 5, i), false);
		hand_out_forks(philo, table->forks, i);
	}
	return (true);
}

static bool	allocate_philos(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return ((free(table), false));
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return ((free_table(table, 1, 0)), false);
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return ((free_table(table, 2, 0)), false);
	table->forks = malloc(sizeof(t_fork) * table->num_of_philos);
	if (!table->forks)
		return ((free_table(table, 3, 0)), false);
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return ((free_table(table, 4, i)), false);
		i++;
	}
	if (inform_philos(table) == false)
		return (false);
	return (true);
}

bool	set_table(t_table *table, char **argv)
{
	if (initialize_input(table, argv) == false)
		return (false);
	if (allocate_philos(table) == false)
		return (false);
	return (true);
}
