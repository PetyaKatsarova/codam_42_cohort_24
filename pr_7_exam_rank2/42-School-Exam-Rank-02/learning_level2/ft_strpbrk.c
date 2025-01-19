#include <stdio.h>
#include <string.h>

char *ft_strpbrk(const char *s1, const char *s2)
{
    int i = 0;
    while (*s1)
    {
        const char *s2_cpy;
        s2_cpy = s2; // address to address
        while (*s2_cpy)
        {
            if (*s1 == *s2_cpy)
                return (char *)s1;
            s2_cpy++;
        }
        s1++;
    }

    return (NULL);
}

int main()
{
    char *bla;
    bla = ft_strpbrk("hello world", " ");
    printf("ft: bla = %s\n", bla);
    printf("or: bla = %s\n", bla);

    bla = ft_strpbrk("hello world", "xyz");
    printf("ft: bla = %s\n", bla);
    printf("or: bla = %s\n", bla);

    bla = ft_strpbrk("hello world", "");
    printf("ft: bla = %s\n", bla);
    printf("or: bla = %s\n", bla);

    bla = ft_strpbrk("hello world", "xyo");
    printf("ft: bla = %s\n", bla);
    printf("or: bla = %s\n", bla);
    return (0);
}