#include <stdio.h>
/**
 * returns 0 if strings are equal
 * - if s1 < s2 and + if s1 > s2
*/

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

int main(int argc, char **argv)
{
    (void) argc;
    printf("result = %d\n", ft_strcmp(argv[1], argv[2]));
    return (0);
}