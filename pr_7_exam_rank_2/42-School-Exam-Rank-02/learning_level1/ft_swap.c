#include <stdio.h>

void    ft_swap(int *a, int *b)
{
    int temp = *a; // store val of *a in temp
    *a = *b; // assign val of *b to *a
    *b = temp;
}

int main()
{
    int i = 42;
    int j = 3702;
    int *ptr_i = &i;
    int *ptr_j = &j;

    ft_swap(ptr_i, ptr_j);
    printf("i = %d; j = %d\n", *ptr_i, *ptr_j); // 3702, 42


    

    /** NB!!! 
     * 
     * A pointer is a variable that stores the memory address of another variable.
       A pointer to an integer stores the address of an integer variable.
     * 
    */
    int x = 42;       // Regular integer variable
    int *ptr = &x;    // Pointer to the memory address of x

    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", &x);
    printf("Value stored in ptr (address of x): %p\n", ptr); // adress of x
    printf("Value pointed to by ptr: %d\n", *ptr); // values of x(ptr)
}