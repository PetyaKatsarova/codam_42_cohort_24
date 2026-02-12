/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:42:48 by pekatsar          #+#    #+#             */
/*   Updated: 2025/03/15 08:57:20 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/*
int     *ft_range(int start, int end);

It must allocate (with malloc()) an array of integers, fill it with consecutive
values that begin at start and end at end (Including start and end !), then
return a pointer to the first value of the array.

Examples:

- With (1, 3) you will return an array containing 1, 2 and 3.
- With (-1, 2) you will return an array containing -1, 0, 1 and 2.
- With (0, 0) you will return an array containing 0.
- With (0, -3) you will return an array containing 0, -1, -2 and -3.
*/

int     *ft_range(int start, int end)
{
    int i = 0, len;
    int *arr;

    if (start <= end )
        len = end - start + 1; // 7 --2 + 1= 10
    else
        len = start - end + 1;
    
    arr = malloc(sizeof(int) * len);
    if (!arr) return (NULL);
    if (start <= end)
    {
        while (start <= end)
        {
            arr[i++] = start++;
        }
    }
    else
    {
        while (start >= end)
            arr[i++] = start--;
    }
    return (arr);
}
// cc -Wall -Wextra -Werror ft_range2.c && ./a.out
// cc -g -Wall -Wextra -Werror ft_range2.c && valgrind --leak-check=full ./a.out
int main()
{
    // int start = 1, end = 3, i = 0;
    // int start = 0, end = 0, i = 0;
    int start = -1, end = 2, i = 0;
    int *bla = ft_range(start, end);
    if (!bla) return (-1);

    while (start <= end)
    {
        printf("%d * ", bla[i]);
        i++;
        start++;
    }
    printf("\n");
    free(bla);

    int start2 = 0, end2 = -3;
    i = 0;
    int *bla2 = ft_range(start2, end2);
    if (!bla2) return (-1);

    while (start2 >= end2)
    {
        printf("%d * ", bla2[i]);
        i++;
        start2--;
    }
    printf("\n");
    free(bla2);
    return (0);
}
