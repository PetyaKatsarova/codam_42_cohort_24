#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int str_len(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int main(int argc, char **argv)
{
    int     word_len, s_len;
    char    *str;
    char    *word;

    if (argc == 2)
    {
        str = argv[1];
        s_len = str_len(str);
 
        while (s_len > 0) // includes '\0'
        {
            // not needed here but a good practise
            while (s_len > 0 && str[s_len - 1] == ' ')
                s_len--;

            word_len = 0;
            while (s_len > 0 && !(str[s_len-1] == ' ' || str[s_len-1] == '\t'))
            {
                word_len++;
                s_len--;
            }
            word = malloc(sizeof(char) * (word_len+1));
            if (!word)
                return (-1);
     
            for (int i = 0; i < word_len; i++)
                word[i] = str[s_len + i];
            word[word_len] = '\0';

            write (1, word, word_len);
            free(word);

            if (s_len > 0)
            {
                write(1, " ", 1);
                s_len--;
            }            
        }
    }
    write(1, "\n", 1);
    return (0);
}