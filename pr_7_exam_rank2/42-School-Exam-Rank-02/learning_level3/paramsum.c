#include <unistd.h>
#include <stdio.h>

// int num_len(int num)
// {
//     long i;
//     while (num / 10 > 0)
//     {
//         i++;
//     }
//     printf("num_len: %d\n", i);
//     return (i);
// }

void ft_itoa(int num)
{  
    int i = 0;
    char c;
    if (num == 0)
        write(1, "0", 1);
    while (num > 0)
    {
        c = (num % 10) + '0';
        num = num / 10;
        i++;
    }
    printf("num_len: %d; int: %c\n", i, c);
    write(1, "\n", 1);
}

int main(int argc, char **argv)
{
    int n = argc - 1;
    ft_itoa(n);

    printf("argc: %d\n", n);
    // write(1, &str_int, 1); // cant write directly int ! only str!!
    write(1, "\n", 1);
    return (0);
}