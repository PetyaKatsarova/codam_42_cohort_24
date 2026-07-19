#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

// #define BUFFER_SIZE 2000 safer with struct stat st: fstat(fd, &st)

int width_len(char *buf)
{
    int i = 0;
    while (buf[i] && buf[i] != '\n')
        i++;
    return i;
}

/* 
validate map: all ., X, or \n, all width and height lines r the same size,
return 1 on success, 0 if err; write in *widht, *height the sizes
*/
int validate_map(char *buf, int *width, int *height)
{
    int i = 0, h = 0, len = 0;
    int w = width_len(buf);

    if (w == 0)
        return 0;

    while (buf[i])
    {
        if (buf[i] == '\n')
        {
            if (len != w)
                return 0;
            len = 0;
            h++;
        }
        else if (buf[i] != 'X' && buf[i] != '.')
            return 0;
        else
            len++;
        i++;
    }
    if (len > 0)
    {
        if (len != w) 
            return 0;
        h++;
    }
    if (h == 0)
        return 0;
    *width = w;
    *height = h;
    return 1;
}

/*
floodfill: recursive through all neighbours and spots an island: changing the island's X to V, starting from given position: col_i(inner arr: width), row_i(outer arr: height)
returns size of island or 0 on err or buf[i] = '.'
*/
int floodfill(char *buf, int w, int h, int col_i, int row_i)
{
    int size, i;

    if (col_i < 0 || col_i >= w || row_i < 0 || row_i >= h)
        return 0;
    
    size = 1;
    i = row_i * (w + 1) + col_i; // todo: err
    if (buf[i] != 'X') return 0;
    buf[i] = 'V';    
    size += floodfill(buf, w, h, col_i, row_i + 1);
    size += floodfill(buf, w, h, col_i, row_i - 1);
    size += floodfill(buf, w, h, col_i - 1, row_i);
    size += floodfill(buf, w, h, col_i + 1, row_i);
    return size;
}

int largest_island(char *buf, int w, int h)
{
    int largest = 0;
    int size = 0;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int idx = i * (w + 1) + j;
            if (buf[idx] == 'X')
            {
                size = floodfill(buf, w, h, j, i);
                if (size > largest)
                    largest = size;
            }
        }
    }
    return largest;
}

// write ot stdout size of biggest island
void putnbr(int n)
{
    if (n > 9)
        putnbr(n / 10);
    char c = (n % 10) + '0';
    write(1, &c, 1);
}


int main(int argc, char **argv)
{
    int fd, bytes, width, height, largest;
    char *buf;
    struct stat st;

    if (argc != 2)
        return (write(1, "\n", 1), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (write(1, "\n", 1), 1);
    if (fstat(fd, &st) < 0)
        return (write(1, "\n", 1), 1);
    // buf = malloc(BUFFER_SIZE + 1);
    buf = malloc(st.st_size + 1);
    if (!buf)
        return (close(fd), write(1, "\n", 1), 1);
    // bytes = read(fd, buf, BUFFER_SIZE);
    bytes = read(fd, buf, st.st_size);
    if (bytes < 0)
        return (close(fd), free(buf), write(1, "\n", 1), 1);
    buf[bytes] = '\0';
    close(fd);
    if (!validate_map(buf, &width, & height))
        return (free(buf), write(1, "\n", 1), 1);    
    largest = largest_island(buf, width, height);
    putnbr(largest);
    write(1, "\n", 1);
    free(buf);
    return 0;
}
