#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *tab, int low, int high)
{
    int pivot = tab[high];  // Choose last element as pivot
    int i = low - 1;  // Track smaller elements
    
    for (int j = low; j < high; j++)
    {
        if (tab[j] < pivot)  // If current element is smaller than pivot
        {
            i++;  // Move index of smaller element
            swap(&tab[i], &tab[j]);  // Swap smaller element to left
        }
    }
    swap(&tab[i + 1], &tab[high]);  // Place pivot at correct position
    return i + 1;  // Return pivot index
}


void quicksort(int *tab, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(tab, low, high);
        quicksort(tab, low, pivot - 1);
        quicksort(tab, pivot + 1, high);
    }
}
// cc quick_sort.c && ./a.out
int main()
{
    int my_array[5] = {1, 2, -2, 0, 42};
    quicksort(my_array, 0, 4);
    
    for (int i = 0; i < 5; i++)
    {
        printf("[%d] %d\n", i, my_array[i]);
    }
    return 0;
}
