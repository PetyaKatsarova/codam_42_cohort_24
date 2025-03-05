#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int len(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strdup(char *src)
{
    char    *new;
    int     i = 0;
    int     length = len(src);
    new = malloc(sizeof(char) * (length + 1));
    if (!new)
        return (NULL);
    while (src[i])
    {
        new[i] = src[i];
        i++;
    }
    new[i] = '\0';
    return new;
}

int main()
{
    char *dup = ft_strdup("tra la al");
    printf("ft dup: %s, address: %p\n", dup, &dup);
    printf("or dup: %s, address: %p\n", dup, &dup);
}