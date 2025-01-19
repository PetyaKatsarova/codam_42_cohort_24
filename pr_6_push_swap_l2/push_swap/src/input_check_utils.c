/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 16:32:43 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 11:43:43 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Checks if the character is a digit.
 * @param c The character to check.
 * @return 1 if true, 0 otherwise.
 */
int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * Checks if the character is a '+' or '-' sign.
 * @param c The character to check.
 * @return 1 if true, 0 otherwise.
 */
int	is_sign(char c)
{
	return (c == '+' || c == '-');
}

/**
 * Compares two strings of digits.
 * If one starts with a '+' sign, it is ignored.
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return 0 if the strings match, non-zero otherwise.
 */
int	nbstr_cmp(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1[i] == '+')
	{
		if (s2[j] != '+')
			i++;
	}
	else
	{
		if (s2[j] == '+')
			j++;
	}
	while (s1[i] != '\0' && s2[j] != '\0' && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

/**
 * Counts the number of strings in a NULL-terminated array.
 * @param str The array of strings to count.
 * @return The number of strings in the array.
 */
int	count_words(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*chr;

	chr = (char *)s;
	while (*chr != (char)c)
	{
		if (!*chr)
			return (0);
		chr++;
	}
	return (chr);
}
