#include "include/philo.h"

// void	print_data_debug(t_data *data)
// {
// 	int	i;

// 	printf("=== Parsed Arguments ===\n");
// 	printf("count: %d, die: %lu, eat: %lu, sleep: %lu, times_eat: %d\n",
// 		data->args.ph_count, data->args.time_to_die,
// 		data->args.time_to_eat, data->args.time_to_sleep,
// 		data->args.num_if_times_to_eat);

// 	if (!data->forks)
// 		printf("forks not allocated\n");
// 	else
// 		printf("forks allocated at %p\n", (void *)data->forks);

// 	if (!data->philos)
// 		printf("philos not allocated\n");
// 	// else
// 	// {
// 	// 	printf("=== Philosopher Details ===\n");
// 	// 	i = 0;
// 	// 	while (i < data->args.ph_count)
// 	// 	{
// 	// 		printf("Philo %d | left: %p | right: %p | meals: %d | last: %lu\n",
// 	// 			data->philos[i].id,
// 	// 			(void *)data->philos[i].left_fork,
// 	// 			(void *)data->philos[i].right_fork,
// 	// 			data->philos[i].meals_eaten,
// 	// 			data->philos[i].last_meal);
// 	// 		i++;
// 	// 	}
// 	// }
// 	printf("print_mutex address: %p\n", (void *)&data->print_mutex);
// }


int	main(int argc, char **argv)
{
	t_data	data;
	argv_t	args;
	int		i;

	if (init_args(&args, argc, argv))
	{
		return (1); // todo: handle
	}
	if (init_data(&args, &data))
	{
		printf("Initialization failed\n");
		return (1); // todo: handle
	}

	// ✅ Join philosopher threads to avoid leaks
	i = 0;
	while (i < args.ph_count)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	return (0);
}
