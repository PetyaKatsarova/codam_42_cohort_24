#include <unistd.h>

void print_str(char *str)
{
    int i = 0;
    char *temp = str;
    

    while (temp[i])
    {
        if (temp[i+1] == ' ' || temp[i+1] == '\t' || temp[i+1] == '\0')
        {
            if (temp[i] >= 'a' && temp[i] <= 'z')
            {
                temp[i] = temp[i] - 'a' + 'A';
            }
        } else if (temp[i] >= 'A' && temp[i] <= 'Z')
            temp[i] = temp[i] - 'A' + 'a';
        write(1, &temp[i], 1);
        i++;
    }
}

int main(int argc, char **argv)

{   int i = 1;
    if (argc > 1)
    {
        while (argv[i])
        {
            print_str(argv[i]);
            write(1, "\n", 1);
            i++;
        }
    }
    else
        write(1, "\n", 1);
    return (0);
}