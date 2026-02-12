#include <unistd.h>

char *rev_print(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    for (int j = i - 1; j >= 0; j--)
        write(1, &str[j], 1);
    write(1, "\n", 1);
    return (str);
}

int main()
{   
    rev_print("Hello world");
    write (1, "\n", 1);
    rev_print("tnirp esreveR");
    write (1, "\n", 1);
    rev_print("");
    write (1, "\n", 1);
    return (0);
}