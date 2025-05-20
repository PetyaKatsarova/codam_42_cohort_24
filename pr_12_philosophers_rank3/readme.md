
Overview

• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
• The philosophers take turns eating, thinking, and sleeping.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
• There are also forks on the table. There are as many forks as philosophers.
• Since eating spaghetti with just one fork is impractical, a philosopher must pick up
both the fork to their right and the fork to their left before eating.
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
• Every philosopher needs to eat and should never starve.
• Philosophers do not communicate with each other.
• Philosophers do not know if another philosopher is about to die.
• Needless to say, philosophers should avoid dying!

Global rules

• Global variables are forbidden!
• Your program(s) must take the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: The number of philosophers and also the number
of forks.
◦ time_to_die (in milliseconds): If a philosopher has not started eating within
time_to_die milliseconds since the start of their last meal or the start of the
simulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
• Each philosopher has a number ranging from 1 to number_of_philosophers.
• Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher, numbered N, sits between philosopher N - 1 and philosopher
N + 1.

About the logs of the program:
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
• A displayed state message should not overlap with another message.
• A message announcing a philosopher’s death must be displayed within 10 ms of
their actual death.
• Again, philosophers should avoid dying!
Your program must not have any data races.

Program name philo
Turn in files Makefile, *.h, *.c, in directory philo/
Makefile NAME, all, clean, fclean, re
Arguments number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
External functs. memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

Description Philosophers with threads and mutexes

• Each philosopher must be represented as a separate thread.
• There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, they will have access to just one fork.
• To prevent philosophers from duplicating forks, you should protect each fork’s state
with a mutex.

Bonus part
Program name philo_bonus
Turn in files Makefile, *.h, *.c, in directory philo_bonus/
Makefile NAME, all, clean, fclean, re
Arguments number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
External functs. memset, printf, malloc, free, write, fork, kill,
exit, pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday, waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink

Description Philosophers with processes and semaphores
The program of the bonus part takes the same arguments as the mandatory program.
The specific rules for the bonus part are:
• All the forks are put in the middle of the table.
• They have no states in memory, but the number of available forks is represented by
a semaphore.
• Each philosopher must be represented as a separate process. However, the main
process should not act as a philosopher.

