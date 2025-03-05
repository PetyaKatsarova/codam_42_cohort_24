#include <stdlib.h>
#include <stdio.h>

int words_count(char *str)
{
    int i = 0;
    int count = 0;;

    while (str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;
        count++;
        while (str[i]  && !(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;
    }
    return (count);
}

char    **ft_split(char *str)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int start = 0;
    int word_len = 0;
    char **arr;
    int wc = words_count(str);
    arr = malloc(sizeof(char *) * (wc + 1));

    if (!arr)
        return (NULL);
    while (str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;
        start = i;
        while (str[i] && !(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;
        word_len = i - start;
        if (word_len > 0)
        {
            arr[j] = malloc(sizeof(char) * (word_len + 1));
            if (!arr[j])
            {
                while (j-- > 0)
                    free(arr[j]);
                free(arr);
                return NULL;
            }
            for (k = 0; k < word_len; k++)
                arr[j][k] = str[start + k];
            arr[j][k] = '\0';
            j++;
        }
    }
    arr[j] = NULL;
    return (arr);
}

/**
 * THEORY: there is a difference between arr[j] = NULL; and arr[j] = '\0'; because they operate on different types of data and have different purposes.
 * arr[j] = NULL;
Purpose: Used to terminate an array of pointers (char **arr).
Type: NULL is a special constant indicating a null pointer ((void *)0 in C).
Use Case: Commonly used to mark the end of an array of pointers.
char *arr[] = {"Hello", "World", NULL}; // Marks the end of an array of strings.
arr[j] = '\0';
Purpose: Used to terminate a string (an array of char).
*/
int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s \"string to split\"\n", argv[0]);
        return 1;
    }
    char *str = argv[1];
    char **arr = ft_split(str);
    int i = 0;
    if (!arr) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    while (arr[i])
    {
        printf("[%d] %s\n", i, arr[i]);
        free(arr[i]);
        i++;
    }
    free(arr);

    return (0);
}

