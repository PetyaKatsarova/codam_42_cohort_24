#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int is_num(char *str)
{
    int i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] > '9' || str[i] < '0')
            return (0);
        i++;
    }
    return (1);
}
// doesnt care for -num cause is handled in main
int ftatoi(char *str)
{
    int i = 0;
    int num = 0;

    if (!is_num(str))
        return (-1); // simple quick, not best way
    if (str[0] == '-')
        return (-1); // enough for this case
    if (str[0] == '+')
        i++;    
    while (str[i])
    {
        num = num * 10 + str[i] - '0';
        i++;
    }
    return (num);
}

int is_prime(int num)
{
    int i = 2;
    if (num < 2)
        return (0);

    while (i * i <= num)
    {
        if (num % i == 0)
            return (0);
        i++;
    }
    return (1);
}

int sum_primes(int num)
{
    int sum = 0;
    int i = 2;
    if (num < 2) // !! 2 is prime
        return (0);
    while (i <= num)
    {
        if (is_prime(i))
            sum += i;
        i++;
    }
    return (sum);
}

void print_num(int num)
{
    int digit;

    if (num > 9)
        print_num(num / 10);
    digit = num % 10 + '0';
    write(1, &digit, 1);
}

// cc -Wall -Wextra -Werror prime_sum.c && ./a.out

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int num, sum;

        // nth done if not valid num! assume it is, prints -1
        if (argv[1][0] == '-' && is_num(argv[1]))
        {
            write(1, "0", 1);
            return (0);
        }
        // printf("%d\n", ftatoi(argv[1]));
        num = ftatoi(argv[1]);
        sum = sum_primes(num);
        // printf("sum: %d\n", sum);
        print_num(sum);
    }
    else
        write(1, "0", 1);
    write(1, "\n", 1);
    return (0);
}
