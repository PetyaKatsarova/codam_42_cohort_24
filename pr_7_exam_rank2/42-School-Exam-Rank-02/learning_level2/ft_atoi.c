#include <stdio.h>

int ft_atoi(const char *str)
{
    int i = 0;
    int result = 0; // if no digit return 0
    int sign = 1;
    while (str[i] == 32) // white spaces are more: \t, \v, \n, \f, \r
        i++;
    while (str[i])
    {
        if (str[i] == '+')
            i++;
        else if (str[i] == '-')
        {
            i++;
            sign = -1;
        }
        if (str[i] >= '0' && str[i] <= '9')
        {
            result = result * 10 + str[i] - '0';
            i++;
        }
        else
            break; // stop at first not digit char
            // doesnt cover over/underflow
    }
    return (result * sign);
}

int main(int argc, char **argv)
{
    (void) argc;
    printf("result is: %d\n", ft_atoi(argv[1]));
    return (0);
}