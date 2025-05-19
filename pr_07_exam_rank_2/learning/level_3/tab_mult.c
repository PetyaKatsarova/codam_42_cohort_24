#include <stdio.h> // for printf
#include <unistd.h>

int ft_atoi(char *num)
{
    int result = 0; // if not initialized was weird num....
    int i = 0;
    while (num[i] == ' ' || (num[i] >=9 && num[i] <= 13))
        i++;
    while (num[i])
    {
        result = result * 10 + (num[i] - '0');
        i++;
    }
    return (result);
}

// NB!! char str[] = "Hello"; // Automatically sizes to 6 (5 characters + '\0')

int putnb(int num)
{
    if (num / 10 > 0)
    {
        putnb(num / 10);
    }
    num = num % 10 + '0';
    write(1, &num, 1);
}

int main(int argc, char **argv)
{
    int num;

    if (argc == 2)
    {
        num = ft_atoi(argv[1]);

        for (int i = 1; i <= 9; i++)
        {
            putnb(i);
            write(1, " x ", 3);
            putnb(num);
            write(1, " = ", 3);
            putnb(i * num);
            write(1, "\n", 1);
        }
    } else
        write(1, "\n", 1);
    return (0);
}