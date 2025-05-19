#include <unistd.h>

/**
 * s1=dest, s2=src
 *  The  strcpy() function copies the string pointed to by src, including the terminating null byte ('\0'), to the buffer pointed to by dest.  The    
       strings may not overlap, and the destination string dest must be large enough to receive the copy.  Beware of buffer overruns!  (See BUGS.)  
 */
char    *ft_strcpy(char *dest, char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int main()
{
    char src[] =  "Hello world! tra la la... :)";
    char dest[1000];
    ft_strcpy(dest, src);

    int i = 0;
    while (dest[i] != '\0')
    {
        write(1, &dest[i], 1);
        i++;
    }
    write(1, "\n", 1);
    return (0);
}
