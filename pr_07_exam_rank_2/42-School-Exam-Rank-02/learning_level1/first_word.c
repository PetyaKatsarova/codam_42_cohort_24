#include <unistd.h>

/*
A word is a section of string delimited by spaces/tabs or by the start/end of
the string.
*/
int main(int argc, char **argv)
{
   int  i;

   i = 0;
   if (argc == 2)
   {
        while (argv[1][i] == 32 || argv[1][i] == 9)
            i++;
        while (argv[1][i] && argv[1][i] != 32 && argv[1][i] != 9)
        {
            write(1, &argv[1][i], 1);
            i++;
        }
   }
    write(1, "\n", 1);
    return (0);
}