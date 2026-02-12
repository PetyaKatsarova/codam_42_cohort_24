/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_write.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/09 11:52:27 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/09 16:15:50 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static void	ft_putnbr_ul(unsigned long n, int fd)
{
	char	c;

	if (n >= 10)
		ft_putnbr_ul(n / 10, fd);
	c = '0' + (n % 10);
	write(fd, &c, 1);
}

static void	ft_putnbr(int n, int fd)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10, fd);
	c = '0' + (n % 10);
	write(fd, &c, 1);
}

void	print_state(char *msg, t_philo *ph)
{
	t_data			*data;
	unsigned long	curr_time;
	size_t			i;

	data = ph->data;
	curr_time = get_time_ms() - data->start_time;
	i = 0;
	while (msg[i])
		i++;
	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->dead_mutex);
	if (!data->dead)
	{
		ft_putnbr_ul(curr_time, 1);
		write(1, " ", 1);
		ft_putnbr(ph->id, 1);
		write(1, " ", 1);
		write(1, msg, i);
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_unlock(&data->print_mutex);
}

void	print_death(t_data *data, unsigned long now, int i)
{
	unsigned long	curr_time;

	curr_time = now - data->start_time;
	ft_putnbr_ul(curr_time, 1);
	write(1, " ", 1);
	ft_putnbr(i, 1);
	write(1, " died\n", 6);
	data->dead = 1;
}
