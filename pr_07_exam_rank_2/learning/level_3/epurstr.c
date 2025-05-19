#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

void str_trunc_end_print(char *str)
{
    int end = ft_strlen(str) - 1;
    int start = 0;
    int spaces = 0;

    while (str[start] == ' ' || str[start] == '\t')
        start++;
    while (end >= start &&( str[end] == ' ' || str[end] == '\t'))
        end--;
    
    while (start <= end)
    {
        if (str[start] == ' ' || str[start] == '\t')
        {
            if (!spaces)
            {
                write(1, " ", 1);
                spaces = 1;
            }
            start++;
        }
        else
        {
            write(1, &str[start++], 1);
            spaces = 0;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
       str_trunc_end_print(argv[1]);
    }
    write(1, "\n", 1);
}
