/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   meta.h                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/21 16:32:41 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/26 23:55:23 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_H
# define META_H

# include <pthread.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

# define ARG_NOT_SET -1

typedef struct s_meta	t_meta;
typedef struct s_philo	t_philo;

typedef enum e_parse_error {
	PE_SUCCESS,
	PE_ARGS,
	PE_OVERFLOW,
}	t_parse_error;

typedef enum e_message {
	MESSAGE_FORK,
	MESSAGE_EAT,
	MESSAGE_SLEEP,
	MESSAGE_THINK,
	MESSAGE_DEAD,
	MESSAGE_TEST,
}	t_message;

typedef enum e_philo_fork {
	PHILO_FORK_LEFT,
	PHILO_FORK_RIGHT,
	PHILO_FORK_COUNT,
}	t_philo_fork;

typedef struct s_args {
	int32_t	philo_count;
	int32_t	time_to_die;
	int32_t	time_to_eat;
	int32_t	time_to_sleep;
	int32_t	max_eat_count;
}	t_args;

typedef struct s_philo {
	uint32_t		id;
	t_meta			*meta;
	pthread_mutex_t	*forks[PHILO_FORK_COUNT];
	int32_t			eat_count;
	pthread_mutex_t	mutex_eat_time;
	pthread_mutex_t	mutex_eat_count;
	unsigned long	last_eat_time;
	pthread_t		thread;
}	t_philo;

typedef struct s_meta {
	pthread_mutex_t	*forks;
	t_philo			*philos;
	bool			philo_failed;
	bool			sim_stop;
	unsigned long	log_start_time;
	pthread_mutex_t	mutex_log;
	pthread_mutex_t	mutex_sync;
	pthread_mutex_t	mutex_running;
	t_args			args;
}	t_meta;

// main.c
void			sim_set_stop(t_meta *meta);
bool			sim_get_stop(t_meta *meta);

// forks.c
int8_t			forks_init(t_meta *meta, size_t count);

// utils.c
void			sleep_ms(unsigned long ms);
unsigned long	get_time_ms(void);

// parse.c
t_parse_error	parse(t_args *args, int argc, char *argv[]);

// simulation.c
int				sim_cleanup(t_meta *meta);
bool			sim_get_stop(t_meta *meta);
void			sim_set_stop(t_meta *meta);
int				sim_start(t_meta *meta);

// libf2.c
void			*ft_calloc(size_t nmemb, size_t size);
long			ft_atol(const char *s);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);

// philo_eat.c
void			philo_update_eat_count(t_philo *p);
int32_t			philo_get_eat_count(t_philo *p);
void			philo_update_eat_time(t_philo *p);
void			philo_init_eat_count_all(t_philo *p, size_t len);

// philo.c
int				philos_init(t_meta *meta, uint32_t count);

// philo_action.c
void			*philo_main(void *arg);

// monitor.c
void			*monitor(t_meta *meta);

// free.c
void			free_philos(t_philo *philos, size_t len);
int				free_mutexes(pthread_mutex_t *arr, size_t len);

// logger.c
void			logger_log(t_philo *p, t_message status);

#endif
