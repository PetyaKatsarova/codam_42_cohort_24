#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int words_count(char *str)
{
    int i = 0, in_word = 0, count = 0;

    while (str[i])
    {
        if (str[i] == ' ' || str[i] == '\t')
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            count++;
            in_word = 1;
        }
        i++;
    }
    return (count);
}

char *cpy_word(char *str, int start, int end)
{
    int i = 0;
    char *word;


    word = malloc(sizeof(char) * (end - start + 1));
    if (!word) return NULL;
    while (start < end)
    {
        word[i++] = str[start++];
    }
    word[i] = '\0';
    return (word);
}

void free_arr(char **arr)
{
    int i = 0;

    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char    **ft_split(char *str)
{
    char    **result;
    int     wc, i = 0, j = 0, start = 0; // -1 edge case for empty string, not ot have empty pointer

    wc = words_count(str);
    if (wc == 0)
        return (NULL);
    result = (char **)malloc(sizeof(char *) * (wc + 1));
    if (!result) return (NULL);

    while (str[i] && j < wc)
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;
        if (str[i] != '\0')
            start = i;
        while (str[i] && !(str[i] == ' ' || str[i] == '\t'))
            i++;
        result[j] = cpy_word(str, start, i); // = NULL; for mem leaks check
        if (!result[j])
        {
            free_arr(result);
            return (NULL);
        }
        j++;
    }
    result[j] = NULL;
    return (result);
}

// cc -Wall -Wextra -Werror ft_split5.c && ./a.out "hwllo qoels bla "
// cc -Wall -Wextra -Werror ft_split5.c && ./a.out ""
// cc -Wall -Wextra -Werror ft_split5.c && ./a.out " "
// cc -g -Wall -Wextra -Werror ft_split5.c && valgrind --leak-check=full ./a.out "hwllo qoels bla "
int main(int argc, char **argv)
{
    (void)argc;
    // if (argc == 2)
    {
        int     wc = words_count(argv[1]);
        char    **result = ft_split(argv[1]); // check = NULL;
        if (!result || !*result)
            return (-1);
        int     i = 0;

        printf("wc check: %d\n", wc);
        while (result[i])
        {
            printf("[%d] %s\n", i+1, result[i]);
            free(result[i]);
            i++;
        }
        free(result);
    }
    return (0);
}
