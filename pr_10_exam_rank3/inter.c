#include <unistd.h>

void ft_putstr(char *str)
{
    int i = 0;

    while (str[i])
        write(1, &str[i++], 1);

}

int ft_check(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return (1);
        str++;
    }
    return (0);
}

void inter_and_print(char *str1, char *str2)
{
    int     i = 0, j = 0;
    char    result[999] = {0};

    if (str1 && str2)
    {
        while (str1[i])
        {
            if (ft_check(str2, str1[i]) && ft_check(result, str1[i]) == 0)
            {
                result[j++] = str1[i];
            }
            i++;
        }
        result[j] = '\0';
        ft_putstr(result);
    }
}
// cc inter.c
// ./a.out "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
// padinto$
// ./a.out ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
// df6ewg4$
// ./a.out "nothing" "This sentence hides nothing" | cat -e
// nothig$
// ./a.out | cat -e
int main(int argc, char **argv)
{

    if (argc == 3)
        inter_and_print(argv[1], argv[2]);
    write(1, "\n", 1);
    return (0);
}