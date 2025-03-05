#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

// takes str: convert to int: atoi
int ft_atoi(char *str)
{
    int i = 0;
    int sign = 1;
    int num = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
        num = num * 10 + str[i] - '0';
        i++;
    }
    return (num * sign);
}
// get sum of all primes included
bool is_prime(int num)
{
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return (false);
    }
    return (true);
}

int sum_primes(int num)
{
    int sum = 0;
    for (int i = 2; i <= num; i++)
    {
        if (is_prime(i))
            sum += i;

    }
    return (sum);
}

void putnb(int num)
{
    int c = 0;
    if (num > 9)
    {
        putnb(num / 10);
    }
    c = (num % 10) + '0';
    write(1, &c, 1);
}

void main(int argc, char **argv)
{
    if (argc == 2) // && argv[1] > 0
    {
        int num = ft_atoi(argv[1]);
        if (num > 0)
        {
            int sum = sum_primes(num);
            printf("num = %d; sum = %d\n", num, sum);
            putnb(sum);
        }
        else
            write(1, "0", 1);
    }
    else
        write(1, "0", 1);

    write(1, "\n", 1);
}