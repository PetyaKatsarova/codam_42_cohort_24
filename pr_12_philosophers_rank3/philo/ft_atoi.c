/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 16:15:20 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/03 16:15:22 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

#include <limits.h>

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * Returns num between 1 and INT_MAX
 */
int	ft_atoi(const char *str)
{
	long	r;
	int		i;

	r = 0;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (!is_digit(str[i]))
		return (-1);
	while (is_digit(str[i]))
	{
		if (r > (INT_MAX - (str[i] - '0')) / 10)
			return (-1);
		r = r * 10 + (str[i++] - '0');
	}
	if (r == 0)
		return (-1);
	return ((int)r);
}

/**
 * Returns num between 1 and ULONG_MAX
 */
unsigned long	ft_atoul(const char *str)
{
	unsigned long	r;
	int				i;

	r = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (r > (ULONG_MAX - (str[i] - '0')) / 10)
			return (0);
		r = r * 10 + (str[i++] - '0');
	}
	if (r == 0)
		return (0);
	return (r);
}
