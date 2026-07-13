#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int BUFFER_SIZE = 2000;
// count first line char len
int width_len(char *buf)
{
    int i = 0;
    while (buf[i] && buf[i] != '\n')
        i++;
    return i;
}

/*
return 1 if not valid, 0 on success;
overwrites width and height: giving the actual 2d size
*/
int validate_map(char *buf, int *width, int *height)
{
    int i =0, len = 0, h = 0;
    int w = width_len(buf);

    if (w == 0) return 1;
    while (buf[i])
    {
        if (buf[i] == '\n')
        {
            if (len != w) return 1;
            len = 0;
            h++;
        }
        else if (buf[i] != 'X' && buf[i] != '.') return 1;
        else
            len++;
        i++;
    }
    if (len != 0)
    {
        if (len != w) return 1;
        h++;
    }
    if (h == 0) return 1;
    *width = w;
    *height = h;
    return 0;
}

/*
return 0 on out of bound or starting on . or size of that island if start on X
*/
int flooldfill(char *buf, int w, int h, int row_i, int col_i)
{
    int size = 1, i;
    
    if (row_i < 0 || row_i > h || col_i < 0 || col_i > w) return 0;

    i = row_i * (w + 1) + col_i;
    if (buf[i] != 'X') return 0;
    buf[i] = 'V';
    size += flooldfill(buf, w, h, row_i, col_i + 1);
    size += flooldfill(buf, w, h, row_i, col_i - 1);
    size += flooldfill(buf, w, h, row_i - 1, col_i);
    size += flooldfill(buf, w, h, row_i + 1, col_i);
    return size;    
}

/*flood each individual cell to count islands around it starting from 0,0*/
int largest_island(char *buf, int w, int h)
{
    int largest = 0, idx, size;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            idx = i * (w + 1) + j;
            if (buf[idx] == 'X')
            {
                size = flooldfill(buf, w, h, i, j);
                if (size > largest)
                    largest = size;
            }
        }
    }
    return largest;
}

// printnb
void putnbr(int n)
{
    if (n > 9)
        putnbr(n / 10);
    char c = (n % 10) + '0';
    write(1, &c, 1);
}


//main read from argv
// gcc -Wall -Werror -Wextra utils.c 
int main(int argc, char **argv)
{
    int fd, bytes, w, h;
    char *buf;

    if (argc != 2)
        return (printf("You need a .txt file to read the islands from.\n"), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (printf("Opening file failed.\n"), 1);
    
    buf = malloc(BUFFER_SIZE);
    if (!buf)
        return (close(fd), printf("Malloc failed.\n"), 1);
    bytes = read(fd, buf, BUFFER_SIZE - 1);
    if (bytes < 1)
        return (close(fd), free(buf), printf("Failed to read from file\n"));
    close(fd);
    buf[bytes] = '\0';

    if (validate_map(buf, &w, &h) == 1)
        printf("ups, map didnt pass validation");
    int result = largest_island(buf, w, h);
    printf("Largest island is %d\n", result);
    free(buf);
    return 0;
}