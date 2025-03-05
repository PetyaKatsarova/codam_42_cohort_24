#include <stdio.h>
#include <stdlib.h>

int words_count(char *str, char delim)
{
    int i = 0, in_word = 0, wc = 0;

    while (str[i])
    {
        if (in_word && str[i] == delim )
            in_word = 0;
        if (str[i] != delim && !in_word)
        {
            in_word = 1;
            wc++;
        }
        i++;
    }
    return (wc);
}

void free_arr(char **arr)
{
    if (!arr)
        return;
    int i = 0;

    while (arr[i])
        free(arr[i++]);
    free(arr);
}

char *word_dup(char *str, int start, int end)
{
    if (!str || start >= end)
        return (NULL);
    int j = 0;
    char *wdup = malloc(sizeof(char) * (end - start + 1));
    
    if (!wdup)
        return (NULL);
    while (start < end)
        wdup[j++] = str[start++];
    wdup[j] = '\0';
    return (wdup);
}

char **ft_split(char *str, char delim)
{
    int i = 0, j = 0, start = 0;
    char **splitted;
    int wc = words_count(str, delim);
    if (wc <= 0)
        return (NULL);

    splitted = malloc(sizeof(char *) * (wc + 1));
    if (!splitted)
        return (NULL);
    while (str[i] && j < wc)
    {
        while (str[i] && str[i] == delim)
            i++;
        start = i;
        while (str[i] && str[i] != delim)
            i++;
        splitted[j] = word_dup(str, start, i);
        if (!splitted[j])
        {
            printf("oops: %s\n", splitted[j-1]);
        }
        j++;
    }
    splitted[j] = NULL;
    return (splitted);
}
/*
-- THEORY --
Incompatible Types (char *result[] vs. char **)

ft_split(str5, '&') returns a pointer to an array of strings (char **).
char *result[] expects an initialized array, but ft_split dynamically allocates memory.
The correct way to store the result is:
char **result = ft_split(str5, '&');
result[] Requires Immediate Initialization

char *result[] is an array of pointers, but you must define its size at compile-time.
Example of correct static initialization:
char *result[] = {"bla", "tra", "lala", NULL}; // OK
However, ft_split(str5, '&') returns dynamic memory, so you must use char **.
*/
// cc -g -Wall -Werror ft_split3.c && valgrind --leak-check=full --track-origins=yes ./a.out
int main()
{
    // char str[] = "&&Hello&w&orld&.";
    // printf("& starts[4]: %d\n", words_count(str, '&'));
    // char str2[] = "Hello&w&orld&.";
    // printf("& in the middle[4]: %d\n", words_count(str2, '&'));
    // char str3[] = "&&Hello&w&orld&&";
    // printf("wc expected[3]: %d\n", words_count(str3, '&'));
    // char str4[] = "&&Hello&w&orld&";
    // printf("start and end[3]: %d\n", words_count(str4, '&'));

    char str5[] = "&&Hello&w&orld&";
    char **result = ft_split(str5, '&');
    int wc = words_count(str5, '&');
    printf("wc: %d\n", wc);
    if (!result)
    {
        printf("split failed\n");
        return (-1);
    }
    for (int i = 0; i < wc; i++)
    {
        printf("[%d] %s\n", i, result[i]);
        free(result[i]);
    }
    free(result);
    return (0);
}