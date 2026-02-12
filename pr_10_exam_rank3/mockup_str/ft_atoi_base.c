/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 15:02:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/11 17:17:53 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi_base(const char *str, int str_base)
{
	int i = 0, sign = 1, num = 0, digit = 0;

	if (str_base < 2 || str_base > 16) return (0); // out of range base
	if (str[i] == '-' || str[i] == '+')
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
			return (0); // invalid input
		if (digit >= str_base) // base 2 has 0 and 1, base 3: has 0,1,2
			return (0); // not valid input
		num = num * str_base + digit;
		i++;
	}
	return (num * sign); // but if not valid num? still get 0!!! TODO
}

// cc -Werror -Wextra -Wall ft_atoi_base.c && ./a.out
//cc -Werror -Wextra -Wall ft_atoi_base.c && ./a.out 2 1111
int main(int argc, char **argv)
{
	if (argc == 3)
	{
		char	*str_base = argv[1];
		char	*str_num = argv[2];
		int		base = ft_atoi_base(str_base, 10);
		int		num = ft_atoi_base(str_num, base);
		printf("base[%d] num: %d\n", base, num);
	}
	write(1, "\n", 1);
	return (0);
}

/*
(0×4na3)+(1×4na2)+(2×4na1)+(3×4na0)
(0×64)+(1×16)+(2×4)+(3×1)
0+16+8+3=27
Final Result
0123(base4)=27(base 10)
*/