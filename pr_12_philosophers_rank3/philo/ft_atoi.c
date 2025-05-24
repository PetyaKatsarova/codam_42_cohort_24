#include "include/philo.h"

static	int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static	int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (is_digit(str[i]))
	{
		result += (str[i] - '0');
		if (is_digit(str[i + 1]))
			result = result * 10;
		i++;
	}
	return (result * sign);
}

unsigned long	ft_atoul(const char *str)
{
	unsigned long	result = 0;
	int				i = 0;

	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (is_digit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}
