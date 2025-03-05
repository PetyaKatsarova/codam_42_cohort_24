#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int count_digits(int nbr)
{
    int i = 0;
    if (nbr == 0)
        return (1);
    while (nbr != 0)
    {
        nbr /= 10;
        i++;
    }
    return (i);
}

int ft_abs(int nbr)
{
    if (nbr < 0)
        return (-nbr);
    return (nbr);
}

char	*ft_itoa(int nbr)
{
    int nbr_len = count_digits(nbr);
    int i = 0;

    if (nbr < 0)
        i++;
    nbr_len += i;

    char *str = malloc(sizeof(char) * (nbr_len + 1));
    if (!str)
        return (NULL);
    
    str[0] = '-';
    str[nbr_len] = '\0';
    while ((nbr_len - 1) >= i)
    {
        str[nbr_len-1] = ft_abs(nbr % 10) + '0';
        nbr = nbr / 10;
        nbr_len--;      
    }
    return str;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    int     i = count_digits(atoi(argv[1]));
    int     input = atoi(argv[1]);
    char    *str = ft_itoa(input);
    printf("int min is: %d\n", INT_MIN);
    if (str)
    {
        printf("[%d]%s\n", i, str);
        free(str);
    } else
        printf("malloc failed in main\n");
    return (0);
}