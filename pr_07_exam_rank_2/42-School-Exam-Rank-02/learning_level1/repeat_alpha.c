#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int i = 0;
    if (argc == 2)
    {
        while (argv[1][i])
        {
            char    c = argv[1][i];
            int count = 0;
            if (c >= 'a' && c <= 'z')
                count = c - 'a' + 1;
            else if (c >= 'A' && c <= 'Z')
                count = c - 'A' + 1;
            else
                count = 1;
            
            for (int j = 0; j < count; j++)
                write(1, &c, 1);
            i++;
        }
    }

    write(1, "\n", 1);
    return (0);
}