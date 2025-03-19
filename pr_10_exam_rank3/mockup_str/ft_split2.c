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

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c=='\n')
		return (1);
	return (0);
}

int words_count(char *str)
{
	int i = 0, count = 0, in_word = 0;

	while (str[i])
	{
		if (is_space(str[i]))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 0;
			count++;
		}
		i++;
	}
	return (count);
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

char *cpy_word (char *str, int start, int end)
{
	int i = 0;
	char *result = malloc(sizeof(char) * (end - start + 1)); // or + 2?
	if (!result) return NULL;

	while (start < end) // ?
	{
		result[i++] = str[start++];
	}
	result[i] = '\0';
	return (result);
}

char **ft_split(char *str)
{
	int i = 0, j = 0, start, wc = words_count(str);
	char **result;

	result = malloc(sizeof(char *) * (wc + 1));
	while (str[i] && j < wc)
	{
		if (is_space(str[i]))
		{
			while (str[i] && is_space(str[i]))
				i++;
		}
		else
		{
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
		i++;
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
		char *str = argv[1];
		char **result = ft_split(str);
		int i = 0;

		while (result[i])
		{
			printf("[%d] %s\n", i, result[i]);
			free(result[i]);
			i++;
		}
		free(result);
    }
    return (0);
}