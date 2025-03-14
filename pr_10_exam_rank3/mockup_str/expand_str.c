/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_str.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 17:05:42 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/13 17:30:46 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
Assignment name  : expand_str
Expected files   : expand_str.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays it with exactly three spaces
between each word, with no spaces or tabs either at the beginning or the end,
followed by a newline.

A word is a section of string delimited either by spaces/tabs, or by the
start/end of the string.

If the number of parameters is not 1, or if there are no words, simply display
a newline.

Examples:

$> ./expand_str "See? It's easy to print the same thing" | cat -e
See?   It's   easy   to   print   the   same   thing$
$> ./expand_str " this        time it      will     be    more complex  " | cat -e
this   time   it   will   be   more   complex$
$> ./expand_str "No S*** Sherlock..." "nAw S*** ShErLaWQ..." | cat -e
$
$> ./expand_str "" | cat -e
$
$>
*/

int str_len(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void print_str(char *str)
{
	int trimmed_start = 0, trimmed_end = str_len(str)-1;


	while (str[trimmed_start] && str[trimmed_start] == ' ')
	{
		trimmed_start++;
	}
	while (trimmed_end > trimmed_start && str[trimmed_end] && str[trimmed_end] == ' ')
	{
		trimmed_end--;
	}
	while (str[trimmed_start] && trimmed_end >= trimmed_start)
	{
		if (str[trimmed_start] == ' ')
		{
			while (trimmed_end >= trimmed_start && str[trimmed_start] && str[trimmed_start] == ' ')
				trimmed_start++;
			if (trimmed_start <= trimmed_end)
				write(1, "123", 3);
		}
		else
		{
			while (trimmed_end >= trimmed_start && str[trimmed_start])
			{
				write(1, &str[trimmed_start], 1);
				trimmed_start++;
			}
		}
	}
}

// cc -Wall -Wextra -Werror expand_str.c && ./a.out
int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *str = argv[1];
		print_str(str);
	}
	write(1, "\n", 1);
	return (0);
}