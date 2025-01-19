#include <unistd.h>

int main(int argc, char **argv)
{
    int     i = 0;
    char    c;

    if (argc == 2)
    {
        while (argv[1][i])
        {
            c = argv[1][i];
            if (c >= 'a' && c <= 'z')
                c = 'z' - (c - 'a');
            if (c >= 'A' && c <= 'Z')
                c = 'Z' - (c - 'A');
            write(1, &c, 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}

/**
 * 'a' = ASCII 97
'z' = ASCII 122
'A' = ASCII 65
'Z' = ASCII 90
 * 
*/