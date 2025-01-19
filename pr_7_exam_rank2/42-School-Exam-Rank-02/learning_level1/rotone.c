#include <unistd.h>

//cat -ev appends $ to see end of line and -v displays none printable chars
int main(int argc, char **argv)
{
    int i = 0;
    char c;
    if (argc == 2)
    {
        while (argv[1][i])
        {
            c = argv[1][i];
            if (c >= 'a' & c <= 'z')
                c = (c - 'a' + 1) % 26 + 'a';
            else if (c >= 'A' & c <= 'Z')
                c = (c - 'A' + 1) % 26 + 'A';
            write(1, &c, 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}