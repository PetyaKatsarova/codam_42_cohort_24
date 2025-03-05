/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 17:02:47 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 11:49:35 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Counts the number of words in a string based on the delimiter.
 */
static int	ft_wordscount(const char *str, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (*str == c)
			flag = 0;
		str++;
	}
	return (count);
}

/**
 * Duplicates a word from the string between the given indices.
 */
static char	*ft_worddup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word || (finish - start <= 0))
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

/**
 * Frees the allocated memory for the split array.
 */
static char	**ft_free(char **split, size_t j)
{
	while (j)
		free(split[--j]);
	free(split);
	return (NULL);
}

/**
 * Fills the split array with words extracted from the string.
 */
static char	**ft_fill_split(char const *s, char **split, char c)
{
	int		start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			split[j++] = ft_worddup(s, start, i);
			if (!split[j - 1])
				return (ft_free(split, j));
			start = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

/**
 * Splits a string into an array of words based on the delimiter.
 */
char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc((ft_wordscount(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_fill_split(s, split, c));
}
