/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_str2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 11:01:15 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/14 15:31:14 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

//cc -Wall -Wextra -Werror expand_str2.c && ./a.out " this        time it      will     be    more complex  " | cat -e
// cc -Wall -Wextra -Werror expand_str2.c && ./a.out "No S*** Sherlock..." "nAw S*** ShErLaWQ..." | cat -e
int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int i = 0, space = 0;
		char *str = argv[1];

		while (str[i] && str[i] == ' ')
			i++;
		while (str[i])
		{
			if (str[i] == ' ')
				space = 1;
			else
			{
				if (space)
					write(1, "   ", 3);
				space = 0;
				write(1, &str[i], 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
