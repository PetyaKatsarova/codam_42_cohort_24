#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
int *ft_range(int start, int end);
Input:

Two integers, start and end, defining a range.
Example: ft_range(3, 7) should generate [3, 4, 5, 6, 7].
Example: ft_range(7, 3) should generate [7, 6, 5, 4, 3].
Output:

A dynamically allocated array of integers containing all numbers from start to end, inclusive.
Constraints:

Memory must be allocated dynamically (malloc).
The function should return a pointer to the first element of the array.
Handles both increasing (start < end) and decreasing (start > end) ranges.
Must include both start and end in the array.
Returns NULL if allocation fails.

!!NB!!
int arrays do not need null termination like strings.
*/

int *ft_range(int start, int end)
{
    int *arr, arr_len, i = 0;

    if (start == end) return (NULL);
    arr_len = (start - end) > 0 ? (start-end+1) : (end - start+1);
    arr = malloc(sizeof(int) * arr_len);
    if (!arr) return NULL;
    while (arr_len > 0)
    {
        if (start - end > 0)
            arr[i] = end++;
        else
            arr[i] = start++;
        arr_len--;
        i++;
    }
    return (arr);
}
// cc -Werror -Wextra -Wall ft_range.c && ./a.out
// cc -g -Werror -Wextra -Wall ft_range.c && valgrind --leak-check=full ./a.out
int main()
{
    int a = 1, b = 5, loop = b - a;
    int *myarr = ft_range(a, b);
    for (int i = 0; i <= loop; i++)
    {
        printf("%d -> ", myarr[i]);
    }
    printf("end\n");
    free(myarr);
    return (0);
}