/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 17:20:11 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/11 19:31:34 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct  s_point
{
int           x;
int           y;
}               t_point;

char **make_arr2d(char **my_map, t_point size)
{
	char	**result;
	int		j = 0;

	result = malloc(sizeof(char *) * size.y);
	if (!result) return (NULL);
	for (int i = 0; i < size.y; i++)
	{
		result[i] = malloc(sizeof(char) * (size.x + 1));
		j = 0;
		while (j < size.x)
		{
			result[i][j] = my_map[i][j];
			j++;
		}
		result[i][j] = '\0';
	}
	return (result);
}

void fill(char **tab, t_point size, t_point begin, char to_fill)
{
	if (begin.x < 0 || begin.x >= size.x || begin.y < 0 || begin.y >= size.y || tab[begin.y][begin.x] != to_fill)
		return;
	tab[begin.y][begin.x] = 'F';
	fill(tab, size, (t_point){begin.x+1, begin.y}, to_fill);
	fill(tab, size, (t_point){begin.x-1, begin.y}, to_fill);
	fill(tab, size, (t_point){begin.x, begin.y+1}, to_fill);
	fill(tab, size, (t_point){begin.x, begin.y-1}, to_fill);
}

void  flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, size, begin, tab[begin.y][begin.x]);
}
// cc -g -Wall -Werror -Wetra flood_fill.c && valgrind --leak-check=full ./a.out
// cc -Wall -Werror -Wextra flood_fill.c && ./a.out 
int main()
{
	t_point size = {8,5};
	char *my_map[] = {
		"11111111",
		"10001001",
		"10010001",
		"10110001",
		"11100001",
	};
	char	**arr2d = make_arr2d(my_map, size);
	t_point	begin = {7, 4}; // last char
	
	for (int i = 0; i < size.y; i++)
		printf("%s\n", arr2d[i]);
	flood_fill(arr2d, size, begin);
	printf("\nFlood fill F:\n");
	for (int i = 0; i < size.y; i++)
		printf("%s\n", arr2d[i]);
	for (int i = 0; i < size.y; i++)
		free(arr2d[i]);
	free(arr2d);
	return (0);
}




