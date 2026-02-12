/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:09:26 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 17:16:01 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Checks if the argument is a valid number.
 * @param argv The argument string to check.
 * @return 1 if the argument is a number, 0 otherwise.
 */
static int	is_number(char *argv)
{
	int	i;

	i = 0;
	if (is_sign(argv[i]) && argv[i + 1] != '\0')
		i++;
	while (argv[i] && is_digit(argv[i]))
		i++;
	if (argv[i] != '\0' && !is_digit(argv[i]))
		return (0);
	return (1);
}

/**
 * Checks for duplicate arguments.
 * @param argv The argument array.
 * @return 1 if there is a duplicate, 0 otherwise.
 */
static int	is_dup(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 1;
		while (argv[j])
		{
			if (j != i && nbstr_cmp(argv[i], argv[j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * Checks if the argument represents zero, including formats like "+0" or "0000".
 * @param argv The argument string to check.
 * @return 1 if the argument is zero, 0 otherwise.
 */
static int	is_zero(char *argv)
{
	int	i;

	i = 0;
	if (is_sign(argv[i]))
		i++;
	while (argv[i] && argv[i] == '0')
		i++;
	if (argv[i] != '\0')
		return (0);
	return (1);
}

/**
 * Validates the arguments for duplicates and correct integer format.
 * @param argv The argument array to check.
 * @return 1 if arguments are valid, 0 otherwise.
 * Doesnt check for int like: 03 (with leading 0)
 */
int	is_correct_input(char **argv)
{
	int	i;
	int	count_zeros;

	count_zeros = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]) || argv[i][0] == '\0')
			return (0);
		count_zeros += is_zero(argv[i]);
		i++;
	}
	if (count_zeros > 1)
		return (0);
	if (is_dup(argv))
		return (0);
	return (1);
}
