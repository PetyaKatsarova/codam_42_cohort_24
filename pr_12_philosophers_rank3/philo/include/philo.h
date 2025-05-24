#include <stdio.h>

typedef struct argvs_s
{
    int             ph_count;
    unsigned long   time_to_die;
    unsigned long   time_to_eat;
    unsigned long   time_to_sleep;
    int             num_if_times_to_eat; // optional
} argv_t;

int             main(int argc, char **argv);
unsigned long	ft_atoul(const char *str);
int         	ft_atoi(const char *str);