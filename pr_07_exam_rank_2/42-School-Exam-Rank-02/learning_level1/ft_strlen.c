#include <unistd.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

void    putnbr(int n)
{
    if (n > 9)
        putnbr(n/10);
    int remainder = n % 10 + '0';
    write(1, &remainder, 1);
}

int main()
{
    char str[] = "tra la";
    int i = ft_strlen(str);
    putnbr(i);
    write(1, "\n", 1);
    return (0);
}