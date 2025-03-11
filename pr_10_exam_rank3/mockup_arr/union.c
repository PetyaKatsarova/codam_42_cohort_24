#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Assignment name  : union
Expected files   : union.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.

The display will be in the order characters appear in the command line, and
will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Example:

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>
*/

void ft_union(char *str1, char *str2)
{
	int seen[256] = {0};
	int i = 0;

	while (str1[i])
	{
		if (!seen[(unsigned int)str1[i]])
		{
			write(1, &str1[i], 1);
			seen[(unsigned int)str1[i]] = 1;
		}
		i++;
	}
	i = 0;
	while (str2[i])
	{
		if (!seen[(unsigned int)str2[i]])
		{
			write(1, &str2[i], 1);
			seen[(unsigned int)str2[i]] = 1;
		}
		i++;
	}	
}
// cc -Wall -Wextra -Werror union.c && ./a.out padinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
// zpadintoqefwjy$

//cc -Wall -Wextra -Werror union.c && ./a.out ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
//df6vewg4thras$
int main(int argc, char **argv)
{
	if (argc == 3)
	{
		char *str1= argv[1];
		char *str2= argv[2];
		ft_union(str1, str2);
	}
	write(1, " \n", 1);
	return (0);
}

