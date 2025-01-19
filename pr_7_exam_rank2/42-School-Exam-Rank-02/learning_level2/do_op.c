#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int result;
    if (argc == 4)
    {
        // arg2=first num, arg3=operation, arg4=second num
        int     num1 = atoi(argv[1]);
        int     num2 = atoi(argv[3]);
        char    op = argv[2][0]; // get char from str
        printf("op = %c\n", op);
        if (op == '*')
            printf("%d\n", num1 * num2);
        else if (op == '/')
            printf("%d\n", num1 / num2);
        else if (op == '+')
            printf("%d\n", num1 + num2);
        else if (op == '-')
            printf("%d\n", num1 - num2);
        else if (op == '%')
            printf("%d\n", num1 % num2);
    }
    else
        write(1, "\n", 1);
    return (0);
}