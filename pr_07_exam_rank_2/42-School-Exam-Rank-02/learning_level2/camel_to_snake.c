#include <unistd.h>
#include <stdlib.h>

//gcc -g camel_to_snake.c -o camel_to_snake
// valgrind --leak-check=full --show-leak-kinds=all ./camel_to_snake "HelloWorld"


// count words
int num_capital_letters(char *str)
{ 
    int i = 0;
    int count = 0;
    while (str[i])
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            count++;
        i++;
    }
    return (count);
}

int str_len(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}
// make new str with _before Capital letter and change to lcase
char    *to_snake(char *str)
{
    char *snake_case;
    int  i = 0;
    int  j = 0;

    snake_case = malloc(sizeof(char) * (str_len(str) + num_capital_letters(str) + 1));
    if (!snake_case)
        return (NULL);
 
    while (str[i])
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            snake_case[j++] = '_';
            snake_case[j++] = str[i++] + 32;
        }
        else
            snake_case[j++] = str[i++];
    }
    snake_case[j] = '\0';
    return (snake_case); // values or address?
}

int main(int argc, char **argv)
{
    int i = 0;
    char *result;
    if (argc == 2)
    {
        result = to_snake(argv[1]);
        write(1, result, str_len(result));
        write(1, "\n", 1);
        free(result);
    }
    return (0);
}

/**
 * THEORY *
 * valgrind --leak-check=full --show-leak-kinds=all ./your_program [arguments]
Explanation:
valgrind:

Launches the Valgrind tool.
--leak-check=full:

Performs a detailed memory leak analysis.
--show-leak-kinds=all:

Displays all types of memory leaks (e.g., definite, possible, reachable).
./your_program [arguments]:

Runs your compiled program with any necessary arguments.
*/