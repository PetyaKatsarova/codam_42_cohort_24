#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sort_int_tab(int *tab, unsigned int size)
{
    unsigned int i = 0;
    int j;
    int temp;

    while (tab[i] && tab[i+1])
    {
        j = i + 1;
        while (tab[j])
        {
            if (tab[i] > tab[j])
            {
                int temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
            j++;
        }
        i++;
    }
}

int main()
{
    int tab[] = {5, 2, 1, 4, 3};
    int size = 5;
    sort_int_tab(tab, size);
    for (int i = 0; i < size; i++)
    {
        printf("[%d] %d\n", i, tab[i]);
    }
    write(1, "\n", 1);
    return (0);
}