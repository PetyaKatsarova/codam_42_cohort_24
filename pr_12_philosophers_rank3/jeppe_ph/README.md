# NOTES


### Forks

* There are as many forks as philosophers.
* Every fork object has its own mutex.

### Philo's

* Each philosopher has a `fork[left]` and `fork[right]` pointer.

### Arguments
* `number_of_philosophers` The number of philosophers and also the number of forks.

* `time_to_die` (in milliseconds): If a philosopher didn’t start eating
  `time_to_die` milliseconds since the beginning of their last meal or the
  beginning of the simulation, they die.

* `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
  During that time, they will need to hold two forks.

* `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.

* `number_of_times_each_philosopher_must_eat` (optional argument): If all
  philosophers have eaten at least `number_of_times_each_philosopher_must_eat`
  times, the simulation stops. If not specified, the simulation stops when a
  philosopher dies.

### Logging
* `timestamp_in_ms` X has taken a fork
* `timestamp_in_ms` X is eating
* `timestamp_in_ms` X is sleeping
* `timestamp_in_ms` X is thinking
* `timestamp_in_ms` X died

* A displayed state message should not be mixed up with another message.

* A message announcing a philosopher died should be displayed no more than 10
  ms after the actual death of the philosopher.



## References

### Mutexes
https://stackoverflow.com/a/40880980


### Volitile and atomic
https://stackoverflow.com/questions/53032354/does-atomic-read-guarantees-reading-of-the-latest-value

## Stuff to learn

`pthread_create`
`pthread_detach`
`pthread_join`
`pthread_mutex_init`
`pthread_mutex_destroy`
`pthread_mutex_lock`
`pthread_mutex_unlock`
