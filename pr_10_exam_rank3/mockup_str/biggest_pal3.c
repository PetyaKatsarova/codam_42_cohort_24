/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biggest_pal3.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 13:48:41 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/13 16:42:02 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : biggest_pal
Expected files   : *.c, *.h
Allowed functions: write
--------------------------------------------------------------------------------

Write a program named biggest_pal that takes a string as argument and prints the
biggest palindrome included inside this string, followed by a newline.

This string contains only lowercase characters.

If there is two palindromes of the same length, you have to print the last one.

If there is more or less than 1 argument, your program must print only a newline
only.

Exemples:

$> biggest_pal "abcba"
abcba
$> biggest_pal "aaaaaaaaaabbcbbaaaa"
aaaabbcbbaaaa
$> biggest_pal "aooibdaoiwhoihwdoinzeldaisaboyobasiadlezfdsfnslk"
zeldaisaboyobasiadlez
$> biggest_pal "aeibaabaammaabaalek"
aabaammaabaa
$> biggest_pal abeb qpinqwjobo qkmnwoiq

$> biggest_pal

$>
*/

#include <unistd.h>

void print_str(char *str, int start, int end)
{
	while (start <= end)
	{
		write(1, &str[start++], 1);
	}
}

int is_pal(char *str, int start, int end)
{
	if (!str || start > end) return (0);

	while (start < end)
	{
		if (str[start++] != str[end--])
			return (0);
	}
	return (1);
}

void print_biggest_pal(char *str)
{
	int i = 0, j = 0, max_len = 0, last_start = 0, last_end = 0, curr_len = 0;

	while (str[i])
	{
		j = i;
		while (str[j])
		{
			if (is_pal(str, i, j))
			{
				curr_len = j - i + 1;
				if (curr_len > max_len || (curr_len == max_len && i > last_start))
				{
					max_len = curr_len;
					last_start = i;
					last_end = j;
				}
			}
			j++;
		}
		i++;
	}
	if (max_len > 0)
		print_str(str, last_start, last_end);
}

//cc -Wall -Wextra -Werror biggest_pal3.c && ./a.out abcba
//cc -Wall -Wextra -Werror biggest_pal3.c && ./a.out aaaaaaaaaabbcbbaaaa
//cc -Wall -Wextra -Werror biggest_pal3.c && ./a.out "aeibaabaammaabaalek"
int main(int argc, char **argv)
{
	if (argc == 2)
	{
		print_biggest_pal(argv[1]);
	}
	write(1, "\n", 1);
	return (0);
}