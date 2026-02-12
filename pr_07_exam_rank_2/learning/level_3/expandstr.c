#include <unistd.h>

int main(int argc, char **argv)
{
    int i = 0;
    int space = 0;
    if (argc == 2)
    {
        char *str = argv[1];
        while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        {
            i++;
        }
        while (str[i])
        {
            if (str[i] == ' ' || str[i] == '\t')
                space = 1;
            if (!(str[i] == ' ' || str[i] == '\t'))
            {
                if (space)
                    write(1, "   ", 3);
                space = 0;
                write(1, &str[i], 1);
            }
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}