/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 16:10:30 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/04 12:35:14 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct argvs_s
{
	int				ph_count;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				num_if_times_to_eat;
}	t_argv;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				taken;
}	t_fork;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	unsigned long	last_meal;
	int				meals_eaten;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	meals_eaten_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_argv			args;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	unsigned long	start_time;
	int				dead;
	t_philo			*philos;
}	t_data;

int				main(int argc, char **argv);

// ft_atoi.c
unsigned long	ft_atoul(const char *str);
int				ft_atoi(const char *str);

// initiation.c
unsigned long	get_time_ms(void);
int				init_args(t_argv *args_struct, int argc, char **argv);
int				init_data(t_argv *argv_struct, t_data *data);

// routines.c
void			*philo_routine(void *ptr);
void			*monitor_routine(void *arg);
int				cleanup_all(t_data *data);
unsigned long	get_time_ms(void);
void	        print_state(char *msg, t_philo *ph);
void			print_death(t_data *data, unsigned long now, int i);

#endif
