/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atoi_base.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/21 09:01:43 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/21 09:55:57 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h> // malloc
#include <stdio.h> // printf

// returns INT from str representing the base num
int	atoi_base(char *str, int base)
{
	int	result = 0,	digit = 0, i = 0, sign = 1;
	if (base < 2 || base > 16) return (-1);

	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}

	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			digit = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			digit = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			digit = str[i] - 'A' + 10;
		else
			return (-1);
		if (digit >= base) return (-1);
		result = result * base + digit;
		i++;
	}
	return (result * sign);
}

// cc -Wall -Werror -Wextra atoi_base.c && ./a.out
int main()
{
	//char *str = "FF"; // 255
	char *str = "FF10";  // 65296
	int result = atoi_base(str, 16);
	printf("tra la la\n");
	printf("result is: %d\n", result);
	return (0);
}
