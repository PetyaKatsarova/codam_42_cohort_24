#include <stdio.h>
#include <unistd.h>

// find start of second word
// if only 1 word: print it: 
// print it all with checking no consequtive space(only 1 space)
// print space and the last word, check again for no space after

/*
I need the index of last no empty char in order to trim end spaces or tabs
*/
int last_char_index(char *str)
{
    int i = 0;
    int last_no_space = 0;

    while (str[i])
    {
        if (!(str[i] == ' ' || str[i] == '\t'))
            last_no_space = i;
        i++;
    }
    return (last_no_space);
}

/*
Returns the index of the end of the first word(after trailing spaces and at least 1 char, doesnt check for space after that).
*/
int first_word_end(char *str)
{
    int i = 0;

    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    while (str[i] && !(str[i] == ' ' || str[i] == '\t'))
        i++;
    return (i);
}

void print_first_word(char *str)
{
    int i = 0;

    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    while (str[i] && !(str[i] == ' ' || str[i] == '\t'))
    {
        write(1, &str[i], 1);
        i++;
    }
}

/* Prints string starting from second word(after char and at least 1 space/tab) and trimms extra spaces(no consecutive ones) */
void print_str(char *str)
{
    int space = 0, i, last_index, end_word; 

    last_index = last_char_index(str);
    end_word = first_word_end(str);
    i = end_word;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    while (i <= last_index)
    {
        if (space == 0 && (str[i] == ' ' || str[i] == '\t'))
        {
            space = 1;
            write(1, " ", 1);
        }
        else if (!(str[i] == ' ' || str[i] == '\t'))
        {
            space = 0;
            write(1, &str[i], 1);
        }
        i++;
    }
}

/*
Checks if the string has more than 1 word
*/
int is_words(char *str)
{
    int i = 0, is_word = 0, is_space = 0;
    int end_i = last_char_index(str);

    while (str[end_i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    while (str[i])
    {
        if (!(str[i] == ' ' || str[i] == '\t'))
            is_word = 1;
        else if (str[i] == ' ' || str[i] == '\t')
        {
            is_space = 1;
        }
        if (is_space && is_word && !(str[i] == ' ' || str[i] == '\t'))
            return (1);
        i++;
    }
    return (0);
}
/*
    cc -Wall -Wextra -Wall rotate_str.c && ./a.out "abc   " | cat -e
    abc$ ✅ -1- 

    cc -Wall -Wextra -Wall rotate_str.c && ./a.out "Que la      lumiere soit et la lumiere fut" | cat -e
    la lumiere soit et la lumiere fut Que$   ✅ -2-

    cc -Wall -Wextra -Wall rotate_str.c && ./a.out  "first" "2" "11000000" | cat -e
    first$ ✅ -3-

    cc -Wall -Wextra -Wall rotate_str.c && ./a.out "     AkjhZ zLKIJz , 23y"
    zLKIJz , 23y AkjhZ  ✅ -4-

    check that prints everywehre ony 1 space and trims start/end empty sp
    cc -Wall -Wextra -Wall rotate_str.c && ./a.out "   bla    bla bla   " | cat -e
  cc -Wall -Wextra -Wall rotate_str.c && ./a.out "     AkjhZ zLKIJz , 23y" | cat -e
 */
int main(int argc, char **argv)
{
    if (argc > 1)
    {
        char *str = argv[1];

        print_str(str);
        if (is_words(str))
            write(1, " ", 1);
        print_first_word(str);
    }
    write(1, "\n", 1);
    return (0);
}
