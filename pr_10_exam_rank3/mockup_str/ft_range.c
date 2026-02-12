/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_range.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 16:42:48 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/14 15:38:59 by pekatsar      ########   odam.nl         */
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
	int *result, i = 0, arr_len;

	if (start <= end)
		arr_len = end - start + 1;
	else
		arr_len = start - end + 1;
	result = malloc(sizeof(int) * arr_len);
	if (!result) return (NULL);
	if (start < end)
	{
		while (start <= end)
			result[i++] = start++;
	}
	else
	{
		while (start >= end)
			result[i++] = end++;
	}

	return (result);
}
// cc -g -Wall -Wextra -Werror ft_range.c && ./a.out
//cc -g -Wall -Wextra -Werror ft_range.c && valgrind --leak-check=full ./a.out
int main()
{
	int start = -1, end = 2;
	int *result = ft_range(start, end);
	for (int i = 0; i < abs(end - start) + 1; i++)
	{
		printf("%d ", result[i]);
	}
	free(result);
	return (0);
}

/*
!!NB!! THEORY!!
An array in C is a collection of elements of the same data type, stored in contiguous memory locations. Arrays allow easy access and manipulation of data using indexing.

Character Arrays (char[])
Character arrays (also called strings) need a null terminator (\0) to indicate the end of the string.
This is because C does not store string length automatically—instead, it relies on \0 to determine where the string ends.

Example:
c
Copy
Edit
char str1[] = "Hello";  // Implicit null terminator '\0' added
char str2[] = {'H', 'e', 'l', 'l', 'o', '\0'}; // Explicit null terminator

// Without '\0', it is just an array, not a valid C string.
char str3[] = {'H', 'e', 'l', 'l', 'o'}; // No '\0' - Unsafe for string functions
Why is \0 needed?
Functions like printf("%s", str); and strlen(str); rely on \0 to stop reading memory.
nteger arrays do not need a null terminator (\0) because they are not variable-length like strings. The size of an integer array is either:

Known at compile-time: int arr[5] = {1, 2, 3, 4, 5};
Manually tracked: You must keep track of the number of elements.
Example:
c
Copy
Edit
int nums1[] = {1, 2, 3, 4, 5};   // No need for '\0', size is known
int nums2[5] = {1, 2, 3};        // Remaining values default to 0
Why no \0?

Integers are not variable-length strings.
We access them using indices and track size manually.
*/