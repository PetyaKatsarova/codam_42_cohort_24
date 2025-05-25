#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // for usleep
#include <sys/time.h> // for gettimeofday

typedef struct argvs_s
{
    int             ph_count;
    unsigned long   time_to_die;
    unsigned long   time_to_eat;
    unsigned long   time_to_sleep;
    int             num_if_times_to_eat; // optional
} argv_t;

typedef struct s_philo
{
    int             id;
    unsigned long   last_meal;
    int             meals_eaten;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data   *data;
} t_philo;

typedef struct s_data
{
    argv_t          args;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    unsigned long   start_time;
    int             dead;
    t_philo         *philos;
} t_data;

int             main(int argc, char **argv);

// ft_atoi.c
unsigned long	ft_atoul(const char *str);
int         	ft_atoi(const char *str);

// initiation.c
int init_args(argv_t *args_struct, int argc, char **argv);
int init_data(argv_t *argv_struct, t_data *data);

void *philo_routine(void *ptr);