#include <stdio.h>
#include <unistd.h>

/*
Write a program that takes a string as a parameter, and prints its words in reverse order.
*/

int str_len(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

void print_word(char *str, int start, int end)
{
    while (start < end+1)
    {
        write(1, &str[start], 1);
        start++;
    }
}

void print_reverse_words(char *str)
{
    int start, end;
    int slen = str_len(str);

    while (slen > 0 && (str[slen-1] == ' ' || str[slen-1] == '\t'))
        slen--;
    while (slen > 0)
    {
        if (!(str[slen-1] == ' ' || str[slen-1] == '\t'))
        {
            end = slen-1;
            while (slen > 0 && !(str[slen-1] == ' ' || str[slen-1] == '\t'))
                slen--;
            start = slen;
            print_word(str, start, end);
        }
        else
        {
            while (slen > 0 && (str[slen-1] == ' ' || str[slen-1] == '\t'))
                slen--;
            write(1, " ", 1);
        }
    }
}
/*
cc -Wall -Wextra -Wall rev_wstr.c && ./a.out "You hate people! But I love gatherings. Isn't it ironic?" | cat -e
ironic? it Isn't gatherings. love I But people! hate You$

cc -Wall -Wextra -Wall rev_wstr.c && ./a.out "abcdefghijklm" | cat -e
abcdefghijklm

cc -Wall -Wextra -Wall rev_wstr.c && ./a.out "Wingardium Leviosa" | cat -e
Leviosa Wingardium$
*/
int main(int argc, char **argv)
{
    if (argc == 2)
    {
        char *str = argv[1];
        print_reverse_words(str);
    }
    write(1, "\n", 1);
    return (0);
}