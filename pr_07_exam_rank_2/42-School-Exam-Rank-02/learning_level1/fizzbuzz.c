#include <unistd.h>

void printnbr(int i)
{
    char digit;
    if (i > 9)
        printnbr(i / 10);
    digit = i % 10 + '0';
    write (1, &digit, 1);
}

int main ()
{
    for (int i = 1; i <= 100; i++)
    {
        if (i % 5 == 0 && i % 3 == 0)
            write(1, "fizzbuzz", 8);
        else if (i % 3 == 0)
            write(1, "fizz", 4);
        else if (i % 5 == 0)
            write(1, "buzz", 4);
        else
            printnbr(i);
        write(1, "\n", 1);
    }
}