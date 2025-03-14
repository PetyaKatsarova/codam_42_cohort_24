/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 15:00:42 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/13 15:43:36 by pekatsar      ########   odam.nl         */
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

int count_words(char *str, char delim)
{
	int in_word = 0, i = 0, count = 0;

	while (str[i])
	{
		if (str[i] == delim)
		{
			in_word = 0;
		}
		else if (str[i] && !in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char *cpy_word(char *str, int start, int end)
{	
	if (end - start < 0 || !str) return (NULL);
	
	int		i = 0;
	char	*word = malloc(sizeof(char) * (end - start + 1));
	if (!word) return (NULL);
	while (start < end && str[i])
		word[i++] = str[start++];
	word[start] = '\0';
	return (word);
}

char    **ft_split(char *str, char c)
{
	int		i = 0, j = 0, start = 0;
	int		wc = count_words(str, c);
	char	*cpy = str;
	char	**result;

	result = malloc(sizeof(char *) * (wc + 1));
	if (!result) return (NULL);
	while (cpy[i] && j < wc)
	{
		while (cpy[i] && cpy[i] == c)
			i++;
		start = i;
		while (cpy[i] && cpy[i] != c)
			i++;
		result[j] = cpy_word(str, start, i);
		if (!result[j])
		{
			while (j > 0)
				free(result[j--]);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
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
        int     wc = count_words(argv[1], ' ');
        char    **result = ft_split(argv[1], ' '); // check = NULL;
        if (!result || !*result)
            return (-1);
        int     i = 0;

        printf("wc: %d\n", wc);
        while (result[i])
        {
            printf("[%d] %s\n", i+1, result[i]);
            free(result[i]);
            i++;
        }
        free(result);
    }
    return (0);
}