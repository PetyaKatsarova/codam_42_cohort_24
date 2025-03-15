/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:00:42 by pekatsar          #+#    #+#             */
/*   Updated: 2025/03/15 08:00:58 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/*
Assignment name  : ft_split
Expected files   : ft_split.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write a function that takes a string, splits it into words, and returns them as
a NULL-terminated array of strings.

A "word" is defined as a part of a string delimited either by spaces/tabs/new
lines, or by the start/end of the string.

Your function must be declared as follows:

char    **ft_split(char *str);
*/
int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}


int count_words(char *str)
{
	int i = 0, count = 0, in_word = 0;

	while (str[i] && is_space(str[i]))
		i++;
	while (str[i])
	{
		if (is_space(str[i]))
			in_word = 0;
		else if (!in_word && !is_space(str[i]))
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

char *cpy_word(char *str, int start, int end)
{
	int i = 0;
	char *word;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word) return (0);
	while (str[i] && start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

void free_arr(char **arr)
{
	int i = 0;
	
	while (arr[i])
	{
		free(arr[i]);
	}
	free(arr);
}

char    **ft_split(char *str)
{
	int i = 0, j = 0, wc = count_words(str), start = 0;
	char **result;

	result = malloc(sizeof(char *) * (wc + 1));
	if (!result) return (NULL);
	
	while (str[i] && j < wc)
	{
		while (str[i] && is_space(str[i]))
			i++;
		start = i;
		while (str[i] && !is_space(str[i]))
			i++;
		result[j] = cpy_word(str, start, i);
		if (!result[j])
		{
			free_arr(result);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL; // forgot this was giving mem err!!!
	return (result);
}


// cc -Wall -Wextra -Werror ft_split2.c && ./a.out "hwllo qoels bla "
// cc -Wall -Wextra -Werror ft_split2.c && ./a.out ""
// cc -Wall -Wextra -Werror ft_split2.c && ./a.out " "
// cc -g -Wall -Wextra -Werror ft_split2.c && valgrind --leak-check=full ./a.out "hwllo qoels bla "
int main(int argc, char **argv)
{
     if (argc == 2)
    {
		char *str = argv[1];
		char **bla = ft_split(str);
		int i = 0;

		while (bla[i])
		{
			printf("[%d]%s\n", i, bla[i]);
			free(bla[i]);
			i++;
		}
		free(bla);
    }
    return (0);
}