#include <stdio.h>
#include <stdlib.h>

int ft_words_count(char *str, char delim)
{
    int i = 0, in_word = 0, words_count = 0;

    while (str[i] == delim)
        i++;
    while (str[i])
    {
        if (str[i] == delim)
            in_word = 0;
        else if (!in_word)
        {
            in_word = 1;
            words_count++;
        }
        i++;
    }
    return (words_count);
}

char *ft_dupword(char *str, int start, int end)
{
    char    *result;
    int     i = 0;

    result = malloc((end - start + 1) * sizeof(char));
    if (!result)
        return (NULL);
    while (start < end)
    {
        result[i++] = str[start++];
    }
    result[i] = '\0';
    return (result);
}

void free_arr(char **arr_str)
{
    int i = 0;

    while (arr_str[i])
    {
        free(arr_str[i]);
        i++;
    }
    arr_str = NULL;
    return ;
}

char **ft_split(char *str, char delim)
{
    int i = 0, j = 0, words_count = ft_words_count(str, delim);
    char **splitted = malloc(sizeof(char *) * (words_count + 1));

    if (!splitted)
        return (NULL);
    while (str[i])
    {
        while (str[i] && str[i] == delim)
            i++;
        int start = i;
        while (str[i] && str[i] != delim)
            i++;
        splitted[j] = ft_dupword(str, start, i);
        if (!splitted[j])
            free_arr(splitted);
        i++;
        j++;
    }
    splitted[j] = NULL;
    return (splitted);
}
int main()
{
    // printf("wc 2: %d\n", ft_words_count("^ss^bla#", '^'));
    // printf("wc 2: %d\n", ft_words_count("ss^^bla#", '^'));
    // printf("wc 3: %d\n", ft_words_count("ss^bla^#^", '^'));
    // printf("wc 3: %d\n", ft_words_count("*ss*bla*#*", '*'));
    char    *str;
    char    **result;
    // int     j;

    str = "*ss*bla*#*";
    result = ft_split(str, '*');
    // j = 0;
    for (int i = 0; i < ft_words_count(str, '*'); i++)
    {
        printf("ss bla: %s\n", result[i]);
        free(result[i]);
    }
    free(result);
    return (0);
}