#include <stdio.h>

char *ft_strrev(char *str)
{
    int i = 0;
    int len = 0;
    char temp;

    while (str[len])
        len++;
    while (i < (len-1))
    {
        temp = str[i];
        str[i] = str[len-1];
        str[len-1] = temp;
        i++;
        len--;
    }
    return (str);
}

int main()
{
    char str[] = "Hello world";
    printf("str: %s\n", str);
    printf("str: %s\n", ft_strrev(str));
}