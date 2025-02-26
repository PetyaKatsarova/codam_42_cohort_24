#include <unistd.h>

void print_str(char *str)
{
    int i = 0;

    while (str[i])
        write(1, &str[i++], 1);
}

int is_dup(char *str, char c)
{
    int pos = 0;

    while (str[pos])
    {
        if (str[pos] == c)
            return (1);
        pos++;
    }
    return (0);
}

/**
 * cc -Wall -Wextra -Werror union.c && ./a.out zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
 * zpadintoqefwjy$
 * ./a.out ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
    df6vewg4thras$
    ./a.out "rien" "cette phrase ne cache rien" | cat -e
    rienct phas$
 * 
*/

int main(int argc, char **argv)
{
    if (argc == 3)
    {
       char *a1 = argv[1];
       char *a2 = argv[2];
       int  i = 0, j = 0;
       char result[999] = {0};

       while (a1[i])
       {
            if (is_dup(result, a1[i]) == 0)
            {
                result[j++] = a1[i];
            }
            i++;
       }
       i = 0;
       while (a2[i])
       {
            if (is_dup(result, a2[i]) == 0)
            {
                result[j++] = a2[i];
            }
            i++;
       }
       result[i] = '\0';
       print_str(result);
    }
    write(1, "\n", 1);
    return (0);
}