/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rostring.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 10:22:30 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/20 10:44:33 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : rostring
Expected files   : rostring.c
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------
Write a program that takes a string and displays this string after rotating it
one word to the left.

Thus, the first word becomes the last, and others stay in the same order.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string.

Words will be separated by only one space in the output.

If there's less than one argument, the program displays \n.

Example:

$>./rostring "abc   " | cat -e
abc$
$>
$>./rostring "Que la      lumiere soit et la lumiere fut"
la lumiere soit et la lumiere fut Que
$>
$>./rostring "     AkjhZ zLKIJz , 23y"
zLKIJz , 23y AkjhZ
$>
$>./rostring "first" "2" "11000000"
first
$>
$>./rostring | cat -e
$
$>
*/

#include <unistd.h>

void print_str(char *str, int start, int end)
{
	while (str[start] && start < end)
	{
		write(1, &str[start], 1);
		start++;
	}
}

int is_space(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

void print_rostring(char *str)
{
	int i = 0, start = 0, end = 0, in_word;

	while (str[i] && is_space(str[i]))
		i++;
	start = i;
	while (str[i] && !is_space(str[i]))
		i++;
	end = i;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
		{
			in_word = 0;
			i++;
		}
		while (str[i] && !is_space(str[i]))
		{
			in_word = 1;
			write(1, &str[i], 1);
			i++;
		}
			write(1, " ", 1);
	}
	print_str(str, start, end);
}
// cc -Wall -Wextra -Werror rostring.c && ./a.out "Que la      lumiere soit et la lumiere fut"
// cc -Wall -Wextra -Werror rostring.c && ./a.out "     AkjhZ zLKIJz , 23y"
// cc -Wall -Wextra -Werror rostring.c && ./a.out "     zLKIJz,23y  " | cat -e
int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *str = argv[1];
		print_rostring(str);
	}
	write(1, "\n", 1);
	return (0);
}


