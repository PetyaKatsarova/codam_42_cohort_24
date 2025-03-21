/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/21 09:56:45 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/21 11:52:31 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
Write a function that converts an integer into a null-terminated string representing the number in a given base (from 2 to 16).
*/

#include <stdlib.h> // malloc
#include <stdio.h> // printf

int ilen(long val, int base)
{
	int i = 0;

	if (val == 0)
		return (1);
	if (base == 10 && val < 0)
		i++;
	if (val < 0)
		val = (-1) * val;
	while (val > 0)
	{
		val = val / base;
		i++; // 5555 / 10(1) = 555 / 10(2) = 55 / 10(3) = 5 / 10 (4) = 0
	}
	return (i);
}

char *ft_itoa_base(int val, int base)
{
	char *result;
	long temp = val;
	int len = ilen(temp, base);

	if (base < 2 || base > 16) return (NULL);

	result = malloc (len + 1);
	if (!result) return (NULL);
	result[len] = '\0';
	if (temp == 0)
		result[0] = '0';
	if (temp < 0)
	 	temp = temp * (-1);
	while (temp > 0 && len > 0)
	{
		if (temp % base < 10)
		{
			result[--len] = temp % base + '0';
		}
		else
			result[--len] = temp % base - 10 + 'A';
		temp = temp / base;
	}
	if (val < 0 && base == 10)
		result[0] = '-';
	return (result);
}


// cc -Wall -Wextra -Werror ft_itoa_base.c && ./a.out
// cc -g -Wall -Wextra -Werror ft_itoa_base.c && valgrind --leak-check=full ./a.out
int main()
{
	char *bla = ft_itoa_base(255, 10);
	printf("%s\n", bla);   // "255"
	free(bla);
	char *bla2 = ft_itoa_base(-255, 10);
	printf("%s\n", bla2);  // "-255"
	free(bla2);
	printf("%s\n", ft_itoa_base(255, 16));   // "FF"
	printf("%s\n", ft_itoa_base(255, 2));    // "11111111"
	printf("%s\n", ft_itoa_base(-42, 2));    // "101010" (no minus!)
	printf("%s\n", ft_itoa_base(0, 10));     // "0"
	return 0;	
}