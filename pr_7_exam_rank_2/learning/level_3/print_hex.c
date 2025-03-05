#include <unistd.h>

int ft_atoi(char *str)
{
    int result = 0;
    int i = 0;

    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result = result * 10 + (str[i] - '0');
        }
        else
        {
            write(1, "enter an int!", 12);
            return (-1);
        }
        i++;
    }
    return (result);
}

void print_hex(int num)
{
    char hex_arr[] = "0123456789absdef";

    if (num >= 16)
        print_hex(num / 16);
    write(1, &hex_arr[num % 16], 1);
}

int main(int argc, char **argv)
{
    int num = -1;
    if (argc == 2)
    {
        num = ft_atoi(argv[1]);
        print_hex(num);
    }
    write(1, "\n", 1);
    return (0);
}