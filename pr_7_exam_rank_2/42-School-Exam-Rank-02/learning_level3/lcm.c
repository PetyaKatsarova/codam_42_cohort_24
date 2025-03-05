#include <stdio.h>

unsigned int    lcm(unsigned int a, unsigned int b)
{
    unsigned int lcm;

    if (a == 0 || b == 0)
        return (0);
        
    if (a > b)
        lcm = a;
    else
        lcm = b;
    
    while (1)
    {
        if (lcm % a == 0 && lcm % b == 0)
        {
            return (lcm);
        }
        lcm++;
    }
}

int main()
{
    printf("lcm: %d\n", lcm(2,4));
    printf("lcm: %d\n", lcm(2,40));
    printf("lcm: %d\n", lcm(10, 5));
    printf("lcm: %d\n", lcm(22,4));
    return (0);
}