#include <stdio.h>

char *ft_strrev(char *str)
{
    int     i = 0;
    int     j = 0;
    char    temp;
    
    while (str[j])
        j++;

    while (i < j)
    {
        temp = str[i];
        str[i] = str[j - 1];
        str[j - 1] = temp;
        i++;
        j--;
    }
    return (str);
}

int main()
{
    // !! NB !!
    //str = "bla bla";
// "bla bla" is a string literal, and string literals in C are stored in read-only memory. Attempting to modify them (as ft_strrev does) results in undefined behavior, often causing a segmentation fault.
//     char *str;
    // str = "bla bla"; // immutable: read only !! nb !!
    char str[] = "bla bla"; // Use a mutable string
    printf("str: %s\n", str);
    printf("rev: %s\n", ft_strrev(str));
    return (0);
}