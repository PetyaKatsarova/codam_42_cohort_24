#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    if (argc == 2)
    {
        int num = atoi(argv[1]);
        if (num == 1)
            printf("1");
  
        for (int i = 2; i <= num; i++)
        {
            if (num % i == 0)
            {
                printf("%d", i);
                if (num == i)
                    break;
                printf("*");
                num = num / i;
                i = 2;
            }
        }
        
    }
    printf("\n");
    return (0);
}