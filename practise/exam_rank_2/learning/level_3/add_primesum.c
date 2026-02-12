#include <stdio.h>
#include <unistd.h>

int is_prime(int num)
{
    int i = 2;

    if (num <= 1)
        return (0);
    while (i * i <= num)
    {
        if (num % i == 0)
            return (0);
        i++;
    }
    return (1);
}

int mini_atoi(char *s)
{
    int num = 0;
    int i =0;

    while (s[i])
    {
        num += num * 10 + s[i++] - '0';
    }
    return (num);
}

void putnbr(int num)
{
    int digit;

    if (num > 9)
        putnbr(num / 10);
    digit = num % 10 + '0';
    write(1, &digit, 1);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int i = 2;
        int num = mini_atoi(argv[1]);
        int sum = 0;
        while (num >= i)
        {
            if (is_prime(i))
                sum += i;
            i++;
        }
        putnbr(sum);
    }
    write (1, "\n", 1);
}