#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BSIZE 2000

int get_w(char *buf)
{
    int i = 0;
    while(buf[i] && buf[i] != '\n')
        i++;
    return i;
}

int validate_map(char *map, int *width, int *height)
{
    int len = 0,i = 0,  w , h = 0;

    w = get_w(map);
    if (w < 1) return -1;
    while (map[i])
    {
        if (map[i] == '\n')
        {
            if (w != len)
                return -1;
            len = 0;
            h++;
        } 
        else if (map[i] != 'X' && map[i] != '.')
            return -1;
        else
            len++;
        i++;
    }
    if (len > 0)
    {
        if (len != w) return -1;
        h++;
    }
    if (h == 0) return -1; // !!
    *width = w;
    *height = h;
    return 0;
}

int floodfill(char *map, int w, int h, int y,  int x)
{
    int size = 1;
    if (y < 0 || y >= h || x < 0 || x >= w) return 0;
    if (map[(size_t)y*(w+1)+x] != 'X') return 0;
    map[(size_t)y*(w+1)+x] = 'v';
    size += floodfill(map, w,h, y, x+1);
    size += floodfill(map, w,h, y, x-1);
    size += floodfill(map, w,h, y+1, x);
    size += floodfill(map, w,h, y-1, x);
    return size;
}

int get_biggest(char *map, int w, int h)
{
    int biggest = 0, size  = 0;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int idx = i * (w + 1) + j;
            if (map[idx] == 'X')
            {
                size = floodfill(map, w, h, i, j);
                if (size > biggest)
                    biggest = size;
            }
        }
    }
    return biggest;
}

void putnbr(int n)
{
    char c;
    if (n > 9)
        putnbr(n/10);
    c = n % 10 + '0';
    write(1,&c, 1);
}

int main(int argc,char **argv)
{
    int  fd = 0, w = 0, h = 0, biggest = 0; // beternot inits?? 0
    char *buf;
    ssize_t bytes;

    if (argc == 1) return 1;
    fd = open(argv[1], O_RDONLY);
    if (fd < 1) return 1;
    buf = malloc(BSIZE + 1);
    if (!buf) return (close(fd), 1);
    bytes = read(fd, buf, BSIZE); //bufsize
    if (bytes < 1) return (close(fd), 1);
    buf[bytes] = '\0';
    close(fd);
    if (validate_map(buf, &w, &h) == -1)
        return (free(buf), 1);
    biggest = get_biggest(buf, w, h);
    free(buf);
    putnbr(biggest);
    write(1, "\n", 1);
    return 0;
}