#include <stdio.h>
#include <stdlib.h>

int     *ft_rrange(int start, int end)
{
    int *result;
    int i = 0;
    int range = end - start;
    if (range < 0)
        range *= -1;
    range += 1; // includes start and end

    result = (int *)malloc(sizeof(int) * range);
    if (result == NULL)
        return (NULL);

    while (i < range)
    {
        if (start < end)
            result[i] = end - i;
        else
            result[i] = end + i;
        i++;
    }

    return (result);
}

//gcc -g -o my_program my_program.c
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./my_program
int main()
{
    int *res;
    // res = ft_rrange(1,4); // 4,3,2,1
    // res = ft_rrange(-1,2);  // 2,1,0,-1
    res = ft_rrange(0, -3); // -3,-2,-1,0
    // res = ft_rrange(2, 2); // 2

    if (!res)
    {
        printf("error allocating memory\n");
        return (1);
    }

// manually readjust the loop: 1 or 4 or...
    for (int i = 0; i < 4; i++)
    {
        printf("[%d] %d ", i, res[i]);
    }

    printf("\n");
    free(res);
    return (0);
}

