#include <stdio.h>
#include ,stdlib.h>

int main(int argc, char **argv)
{
    int num1;
    int num2;
    if (argc == 3)
    {
        num1 = atoi(argv[1]);
        num2 = atoi(argv[2]);
    }
    write(1, "\n", 1);
    return (0);
}