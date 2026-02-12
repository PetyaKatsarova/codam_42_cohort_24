#include <stdio.h> // printf
#include <stdbool.h>
#include <unistd.h> // write

int char_to_int(char c)
{
    if (char >= '0' && char <= '9')
        return (c - '0');
    else if (char >= 'a' && char <= 'f')
        return (c - 'a' + 10);
    else if (char >= 'A' && char <= 'F')
        return (c - 'A' + 10);
}

int ft_atoi_base(char *str, int base)
{
    int i = 0;
    int sign = 1;
    int result = 0;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i]) // wont work for negative num
    {
        if (sign == -1)
        {
            
        }
        result += char_to_int(str[i]);
        i++;
    }

    return (result * sign);
}



int main(int argc, char **argv)
{
    int num = ft_atoi_base("422", 10);
    printf("base 10 for [422]: %d\n", num);


   
    num = ft_atoi_base("1A6", 16); 
    printf("base 16 [1A6]: %x\n", num);

    return (0);
}