#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

 unsigned int    lcm(unsigned int a, unsigned int b)
 {
    unsigned int n;

    if (a == 0 || b == 0)
        return (0);
    
    if (a > b)
        n = a;
    else
        n = b;

    while (1)
    {
        if (n % a == 0 && n % b == 0)
            return (n);
        n++;
    }
 }

 int main(int argc, char **argv)
 {
    (void) argc;
    if (argc != 3)
    {
        printf("Usage: ./program <num1> <num2>\n");
        return (1);
    }

    unsigned int a = atoi(argv[1]);
    unsigned int b = atoi(argv[2]);
    unsigned lowest_m = lcm(a, b);
    printf ("lcm of %u & %u = %u\n", a, b, lowest_m);
    return (0);
 }