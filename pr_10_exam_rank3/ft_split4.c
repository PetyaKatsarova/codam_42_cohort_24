#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int words_count(char *str)
{
    int i = 0, count = 0, in_word = 0;

    while (str[i])
    {
        if (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
            in_word = 0;
        else if (!in_word)
        {
            in_word = 1;
            count++;
        }
        i++;
    }
    return (count);
}

char *cpy_word(char *str, int start, int end)
{
    int     i = 0;
    char    *word;

    word = (char *)malloc(sizeof(char) * (end - start + 1));
    if (!word || !str || start >= end) return (NULL);
    while (start < end)
    {
        word[i++] = str[start++];
    }
    word[i] = '\0';
    return (word);
}

char    **ft_split(char *str)
{
    int i = 0, j = 0, start = 0, wc;
    char **result;

    wc = words_count(str);
    result = malloc(sizeof(char *) * (wc + 1));
    if (!result || wc <= 0) return (NULL);
    while (str[i] && j < wc)
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
            i++;
        start = i;
        while (str[i] && !(str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
            i++;
        result[j] = cpy_word(str, start, i);
        if (!result[j])
        {
            // free prev words
            return (NULL);
        }
        j++;
    }
    result[j] = NULL;
    return (result);
}
// cc -Wall -Wextra -Werror ft_split4.c && ./a.out "hwllo qoels bla "
// cc -g -Wall -Wextra -Werror ft_split4.c && valgrind --leak-check=full ./a.out "hwllo qoels bla "
int main (int argc, char **argv)
{
    if (argc == 2)
    {
        char *str = argv[1];
        char **splitted = ft_split(str);
        if (!splitted)
        {
            return (-1);
        }
        int i = 0;
        
        while (splitted[i])
        {
            printf("[%d] %s\n", i, splitted[i]);
            free(splitted[i]);
            i++;
        }
        free(splitted);
    }
    else
        printf("argc not 2==\n");
    return (0);
}