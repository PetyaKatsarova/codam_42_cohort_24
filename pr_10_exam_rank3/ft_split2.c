#include <stdio.h>
#include <stdlib.h>

int words_count(char *str, char delim)
{
    int i = 0;
    int count = 0;
    int in_word = 0;

    while (str[i])
    {
        if (str[i] == delim)
        {
            if (in_word)
                in_word = 0;
        }
        else
        {
            if (!in_word)
            {
                in_word = 1;
                count++;
            }
        }
        i++;
    }
    return (count);
}

char *ft_strdup(char *str, int start, int end)
{
    if (end <= start)
        return (NULL);
    int i = 0;
    char *dup = malloc(sizeof (char) * (end - start + 1));
    if (!dup)
        return (NULL);

    while (start < end)
    {
        dup[i++] = str[start++];
    }
    dup[i] = '\0';
    return (dup);
}

void free_arr(char **arr)
{
    int i = 0;

    if (!arr)
        return;

    while (arr[i])
    {
        free(arr[i++]);
    }
    free(arr);
}

char **ft_split(char *str, char delim)
{
    int     i = 0, start = 0, j = 0;
    char    **arr;
    int     wc = words_count(str, delim);
    arr = malloc(sizeof(char *) * (wc + 1));
    
    if (!arr)
        return (NULL);
    while (str[i])
    {
        while (str[i] && str[i] == delim)
            i++;
        start = i;
        while (str[i] && str[i] != delim)
            i++;
        arr[j] = ft_strdup(str, start, i);
        if (!arr[j])
        {
            free_arr(arr);
            return (NULL);
        }
        j++;
    }
    arr[j] = NULL;
    return (arr);
}

/**
char str[] = "*bla*tra**lala";
Stored in stack memory.
Can be modified.

Using a pointer (string literal, read-only)
char *str = "*bla*tra**lala";
Stored in read-only memory.
Cannot be modified.

char *words[] = { "bla", "tra", "lala", NULL };
char **tralala = words;
tralala → [ "bla" ] → "bla\0"
          [ "tra" ] → "tra\0"
          [ "lala" ] → "lala\0"
          [ NULL  ]  (marks end of array)

*/
int main()
{
    // char str[] = "*bla*tra**lala";
    // printf("*infront[3]: %d\n", words_count(str, '*'));
    // char str2[] = "bla*tra**lala";
    // printf("*in the middle[3]: %d\n", words_count(str2, '*'));
    // char str3[] = "**bla*tra**lala*";
    // printf("*start&end[3]: %d\n", words_count(str3, '*'));
    // char str4[] = "bla*tra**lala**";
    // printf("*end[3]: %d\n", words_count(str4, '*'));

    char str5[] = "bla*tra**lala**";
    char **tralala = ft_split(str5, '*');
    if (!tralala)
    {
        printf(" ** no tralala **\n");
        return (-1);
    }
    int  wc = words_count(str5, '*');
    for (int i = 0; i < wc; i++)
    {
        if (!tralala[i])
            printf("*** wtf ****");
        printf("[%d]: %s\n", i, tralala[i]);
    }
    free_arr(tralala);
    return (0);
}
