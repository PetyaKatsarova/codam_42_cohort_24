/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_all_correct.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/14 15:23:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 16:39:28 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	is_all_correct(int argc, char **argv)
{
	int		i;
	long	value;

	if (!is_correct_input(argv))
		exit_error(NULL, NULL);
	i = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		if (value < INT_MIN || value > INT_MAX || argv[i][0] == '\0')
			exit_error(NULL, NULL);
		i++;
	}
}

/*
* Returns the absolute value of a given integer.
*/

int	abs_val(int num)
{
	if (num < 0)
		return (-1 * num);
	return (num);
}

/**
 * Splits a single string into arguments and returns an argv-like array.
 * Example: input "43 -4 666" -> output ["43", "-4", "666", NULL].
 * @param input The input string to split.
 * @return A NULL-terminated array of strings or NULL on failure.
 */
char	**split_argv(const char *input)
{
	if (!input)
		return (NULL);
	return (ft_split(input, ' '));
}
