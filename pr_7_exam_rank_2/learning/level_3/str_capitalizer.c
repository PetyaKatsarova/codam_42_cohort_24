#include <unistd.h>
#include <stdio.h>

void print_str(char *str)
{
    int i = 0;
    int is_new_word = 1;
    char *temp = str;
    
    while (temp[i])
    {
        if (temp[i] == ' ' || temp[i] == '\t')
            is_new_word = 1;
        else
        {
            if (is_new_word)
            {
                if (temp[i] >= 'a' && temp[i] <= 'z')
                    temp[i] = temp[i] - 'a' + 'A';
                is_new_word = 0;
            } else if (temp[i] >= 'A' && temp[i] <= 'Z' && is_new_word == 0)
                temp[i] = temp[i] - 'A' + 'a';
        }
        write(1, &temp[i], 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    int i = 1;
    if (argc > 1)
    {
        while (argv[i])
        {
            print_str(argv[i]);
            write(1, "\n", 1);
            i++;
        }
    } else
        write(1, "\n", 1);
    return (0);
}