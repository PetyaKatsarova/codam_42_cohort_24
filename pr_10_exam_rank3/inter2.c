#include <unistd.h>

void print_char(char *str)
{
    int i = 0;

    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

int char_in(char *str, char c)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}
/*
    char result1[10] = {0}; // All elements are '\0'
    char result2[10] = {'0'}; // result2[0] = '0', rest are '\0'

    printf("result1: [%s]\n", result1); // Prints nothing
    printf("result2: [%s]\n", result2); // Prints "0"
*/

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        int i = 0, j = 0;
        char result[999]; // = {0}; // not perfect...
        while (argv[1][i] && argv[2][i])
        {
            if (char_in(argv[2], argv[1][i]) == 1 && char_in(result, argv[1][i]) == 0)
            {
                result[j] = argv[1][i];
                j++;
            }
            i++;
        }
        result[j] = '\0';
        print_char(result);
    }
    write(1, "\n", 1);
    return (0);
}