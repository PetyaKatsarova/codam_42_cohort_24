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

	i = 0;
	main = 0.0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		main = main * 10.0 + (str[i] - '0');
		i++;
	}
	return (main);
}

/**
 * if !is_double() exits with exit failure and prints message
*/
double	str_to_double(char *str)
{
	double	result;
	int		i;
	double	decimal_place;

	if (!is_double(str))
		print_menu_exit();
	result = get_main_part(str);
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
	if (str[0] == '-')
		return (result * -1);
	else
		return (result);
}

int	is_double(char *str)
{
	unsigned int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '.' || str[i] == ',')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		if (str[i] != '\0' && (str[i] < '0' || str[i] > '9'))
			return (0);
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}
