/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 14:10:20 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/14 14:10:20 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

static int	main_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}

static double	get_main_part(char *str)
{
	int		i;
	double	main;
	double	factor;

	i = 0;
	factor = 1.0;
	main = 0.0;
	if (str[0] == '0' && str[1] == '\0')
		return (0.0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			factor = -1.0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		main = main * 10.0 + (str[i] - '0');
		i++;
	}
	return (main * factor);
}

double	str_to_double(char *str)
{
	double	result;
	int		i;
	double	decimal_place;
	int		factor;

	factor = 1;
	result = get_main_part(str);
	if (result < 0)
	{
		result *= -1;
		factor = -1;
	}
	i = main_len(str);
	if (str[i] == '.' || str[i] == ',')
	{
		i++;
		decimal_place = 0.1;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i] - '0') * decimal_place;
			decimal_place /= 10.0;
			i++;
		}
	}
	return (result * factor);
}

int	is_double(char *str)
{
	unsigned int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (EXIT_FAILURE);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '.' || str[i] == ',')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}
