#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int str_len (char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char *first_word(char *str)
{
    int i = 0;
    int j = 0;
    char *word;
    while (*str == ' ' || *str == '\t')
    str++;

    while (str[i] && !(str[i] == ' ' || str[i] == '\t'))
        i++;
   
    word = malloc(sizeof(char) * (i+1));
    if (!word)
        return (NULL);
    while (i > 0)
    {
        word[j] = str[j];
        i--;
        j++;
    }
    word[j] = '\0';
    return (word);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        char    *str = argv[1];
        char    *word = first_word(str);
        int     w_len = str_len(word);
        int     i = 0;

        while (*str == ' ' || *str == '\t') 
            str++;
        while (*str && !(*str == ' ' || *str == '\t')) 
            str++;
        
        while (str[i]) // print the rest, trip to one " "
        {
            if (str[i] == ' ' || str[i] == '\t')
            {
                write(1, " ", 1);
                while (str[i] == ' ' || str[i] == '\t')
                    i++;
            }
            else
            {
                write(1, &str[i], 1);
                i++;
            }
        }
        if (i > 0)
            write(1, " ", 1);
        write(1, word, w_len);
        printf("word len: %d, word: %s\n", w_len, word);
        free(word);
    }
    write(1, "\n", 1);
    return (0);
}