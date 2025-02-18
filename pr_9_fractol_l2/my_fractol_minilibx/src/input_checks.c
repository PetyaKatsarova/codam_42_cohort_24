/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 14:50:00 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/13 16:48:31 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

static int	is_in_range(double d)
{
	return (d >= -2.0 && d <= 2.0);
}

/**
 * EXITS WITH EXIT_FAILURE
*/
void	print_menu_exit(void)
{
	ft_putendl_fd("** Invalid args.", 1);
	ft_putendl_fd("** Type: mandelbrot, julia, tricorn, or phoenix.", 1);
	ft_putendl_fd("** For julia set, you have the option to add", 1);
	ft_putendl_fd("** 2 values between -2 and 2.", 1);
	exit(EXIT_FAILURE);
}

static int	check_julia(int argc, char **argv)
{
	double	num1;
	double	num2;

	if (argc == 2)
		return (1);
	if (!is_double(argv[2]) && !is_double(argv[3]))
		print_menu_exit();
	else
	{
		num1 = str_to_double(argv[2]);
		num2 = str_to_double(argv[3]);
		if (is_in_range(num1) && is_in_range(num2))
			return (1);
		print_menu_exit();
	}
	return (0);
}

int	is_valid_input(int argc, char **argv)
{
	if (argc == 2 && (!ft_strncmp(argv[1], "mandelbrot", 10)
			|| !ft_strncmp(argv[1], "1", 1)))
		return (1);
	if ((argc == 2 || argc == 4) && (!ft_strncmp(argv[1], "julia", 5)
			|| !ft_strncmp(argv[1], "2", 1)))
		return (check_julia(argc, argv));
	if (argc == 2 && (!ft_strncmp(argv[1], "tricorn", 7)
			|| !ft_strncmp(argv[1], "3", 1)))
		return (1);
	if (argc == 2 && (!ft_strncmp(argv[1], "phoenix", 7)
			|| !ft_strncmp(argv[1], "4", 1)))
		return (1);
	print_menu_exit();
	return (0);
}
