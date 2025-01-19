#include <unistd.h> // for write

int main(int argc, char **argv)
{
    int i = 0;
    int j = 0;

    if (argc == 3)
    {
        while (argv[1][i] && argv[2][j])
        {
            if (argv[1][i] == argv[2][j])
                i++; // loop through s1
            j++; // loop through s2
        }
        if (argv[1][i] == '\0')
            write(1, "1", 1);
        else
            write(1, "0", 1);
    }

    write(1, "\n", 1);
    return (0);
}

