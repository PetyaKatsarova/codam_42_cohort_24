/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 09:33:57 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/13 10:52:30 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int words_count(char *str, char c)
{
	int i = 0, in_word = 0, count = 0;
	char	*cpy = str;
	while (cpy[i] && cpy[i] == c)
		i++;
	while (cpy[i])
	{
		if (cpy[i] == c)
			in_word = 0;
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

char *word_cpy(char *str, int start, int end)
{
	char	*result;
	int		i = 0;

	if (start >= end || !str) return (NULL);
	result = malloc(sizeof(char) * (end - start + 1));
	if (!result) return (NULL);
	while (str[start] && (start < end))
	{
		result[i++] = str[start++];
	}
	result[i] = '\0';
	return (result);
}

char **ft_split(char *str, char c)
{
	int		i = 0, start = 0, j = 0, wc;
	char	**result;

	wc 		= words_count(str, c);
	result 	= malloc(sizeof(char *) * (wc + 1));
	if (!result) return (NULL);
	while (str[i] && j < wc)
	{
		while (str[i] && str[i] == c)
			i++;
		start = i;
		while (str[i] && str[i] != c)
			i++;
		result[j] = word_cpy(str, start, i);
		if (!result[j]) return (NULL); // TODO free prev words...
		j++;
	}
	result[j] = NULL;
	return (result);
}

// cc -Wall -Wextra -Werror ft_split.c && ./a.out "hwllo qoels bla "
// cc -Wall -Wextra -Werror ft_split.c && ./a.out ""
// cc -Wall -Wextra -Werror ft_split.c && ./a.out " "
// cc -g -Wall -Wextra -Werror ft_split.c && valgrind --leak-check=full ./a.out "hwllo qoels bla "
int main(int argc, char **argv)
{
     if (argc == 2)
    {
        int     wc = words_count(argv[1], ' ');
        char    **result = ft_split(argv[1], ' '); // check = NULL;
        if (!result || !*result)
            return (-1);
        int     i = 0;

        printf("wc check: %d\n", wc);
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