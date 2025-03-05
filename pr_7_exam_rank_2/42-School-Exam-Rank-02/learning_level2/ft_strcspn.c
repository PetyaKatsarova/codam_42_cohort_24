#include <stdio.h>
#include <string.h>

/**
 * get len of a prefix substring
 * strcspn() function calculates the length of the initial segment of s which consists entirely of bytes not in reject.
 * strcspn() function returns the number of bytes in the initial segment of s which are not in the string reject.
*/

size_t ft_strcspn(const char *s, const char *reject)
{
    int count = 0;
    while (*s)
    {
        const char *r = reject;
        while (*r)
        {
            if (*r == *s)
                return(count);
            r++;
        }
        count++;
        s++;
    }
    return (count);
}

void main()
{
    printf("ft: %ld\n", ft_strcspn("hello world", "zy"));
    printf("or: %ld\n", strcspn("hello world", "zy"));
}