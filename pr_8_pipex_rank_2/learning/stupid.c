#include <stdio.h>

//'"'"'{count++} END {printf "count: %i", count}'"'"''
void wtf(char *command)
{
    int i = 1;
    printf("[%d]%s\n", i++,command);
}

int main(int argc, char **argv)
{
    int i = 0;
    while (argc > 0)
    {
        wtf(argv[i]);
        i++;
        argc--;
    }
}

/**
 *./a.out stupid 'stupid' "extraStupid" '"EvenDumber"' "'''"'The dummest'"'''" '"'"'{count++} END {print count}'"'"''
[0] -- ./a.out --
[1] -- stupid --
[2] -- stupid --
[3] -- extraStupid --
[4] -- "EvenDumber" --
[5] -- '''The dummest''' --


./a.out 'awk '"'"'{count++} END {printf "count: %i", count}'"'"''
*/
/**
 * NB!!!
 * shell removes all outer quotes and any immediate the same!!!!
*/