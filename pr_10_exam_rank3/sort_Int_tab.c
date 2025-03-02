#include <stdio.h>
#include <stdlib.h>

/*
sort (in-place) in ascending order the 'tab' int array, that contains exactly 'size' members. Doubles must be preserved.
this is bubble sort
*/
void sort_int_tab(int *tab, unsigned int size)
{
    for (int i = 0; i < size-1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (tab[j] > tab[j+1])
            {
                int temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
}

void sort_int_tab2(int *tab, unsigned int size)
{
    unsigned int i;
    int *cpy = tab;

    i = 0;
    while (i < size - 1)
    {
        if (cpy[i] > cpy[i + 1])
        {
            int temp = cpy[i];
            cpy[i] = cpy[i + 1];
            cpy[i + 1] = temp;
            i = 0;
        }
        else
            i++;
    }
}

// cc sort_Int_tab.c && ./a.out
// cc -g sort_Int_tab.c && valgrind --leak-check=full ./a.out
int main()
{
    int size = 6;
    int my_array[6] = {1, 2, -2, 0, 42, -37};
    sort_int_tab(my_array, size);
    // sort_int_tab2(my_array, size);
    for (int i = 0; i < size; i++)
    {
        printf("[%d] %d\n", i, my_array[i]);
    }
    return (0);
}