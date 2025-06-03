#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // for usleep
#include <sys/time.h> // for gettimeofday
#include <limits.h> // INT_MAX

typedef struct argvs_s
{
    int             ph_count;
    unsigned long   time_to_die;
    unsigned long   time_to_eat; // mutex for the forks
    unsigned long   time_to_sleep;
    int             num_if_times_to_eat; // optional
} t_argv;

typedef struct s_fork {
    pthread_mutex_t mutex;
    int             taken; // 0 = free, 1 = taken
} t_fork;

typedef struct s_philo
{
    int             id;
    unsigned long   last_meal;
    int             meals_eaten;
    pthread_t       thread;
    t_fork          *left_fork;
    t_fork          *right_fork;
	pthread_mutex_t	meals_eaten_mutex;
    struct s_data   *data;
} t_philo;

typedef struct s_data
{
    t_argv          args;
    t_fork          *forks;
    pthread_mutex_t print_mutex;
	pthread_mutex_t	dead_mutex;
    unsigned long   start_time;
    int             dead;
    t_philo         *philos;
} t_data;

int             main(int argc, char **argv);

// ft_atoi.c
unsigned long	ft_atoul(const char *str);
int         	ft_atoi(const char *str);

// initiation.c
unsigned long	get_time_ms();
int 			init_args(t_argv *args_struct, int argc, char **argv);
int 			init_data(t_argv *argv_struct, t_data *data);

void 			*philo_routine(void *ptr);
void 			*monitor_routine(void *arg);
int 	        cleanup_all(t_data *data);