#include <stdlib.h>
#include <stdio.h>

int     *ft_range(int start, int end)
{
    int range;
    int i = 0;
    int *result;
    
    if (start <= end)
        range = end - start + 1;
    else
        range = start - end + 1;

    result = (int *)malloc(sizeof(int) * range);
    if (!result)
        return (NULL);

    while (i < range)
    {
        if (start <= end)
            result[i] = start + i;
        else
            result[i] = start - i;
        i++;
    }
    return (result);
}

//gcc -g -o my_program my_program.c
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./my_program
int main()
{
    int *result;
    result = ft_range(1, 4); // 1,2,3,4
    result = ft_range(-1, 2); // -1, 0, 1, 2
    result = ft_range(0, 0); // 0
    // result = ft_range(0, -3); // 0, -1, -2, -3
    int i = 0;
    if (result == NULL)
    {
        printf("Memorey allocation failed.\n");
        return (1);
    }
    while (i <= 3)
    {
        printf("[%d] %d ", i, result[i]);
        i++;
    }
    printf("\n");
    free(result);
    return (0);
}