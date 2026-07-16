#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int width_len(char *buf)
{
    int i = 0;
    while (buf[i] != '\n' && buf[i] != '\0')
        i++;
    return i;
}

/*
1. validate: only X, . and \n; each line is == width
2. updated values of w and h of the map(rectangular)
3. return -1 on invalid, 0 on success
*/
int validate_map(char *buf, int *width, int *height)
{
    int h = 0, i = 0, len = 0;
    int w = width_len(buf);

    if (w == 0 || width == 0 || height == 0)
        return -1;
    while (buf[i])
    {
        if (buf[i] == '\n')
        {
            if (len != w)
                return -1;
            len = 0;
            h++;
        }
        else {
            if (buf[i] != 'X' && buf[i] != '.')
                return -1;
            len++;
        }
        i++;
    }
    if (len > 0)
    {
        if (len != w)
            return -1;
        h++;
    }
    if (h == 0) return -1;
    *width = w;
    *height = h;
    return 0;
}

/*
1. return 0 if no island, or size of island
2. start from coordinates coli, row1
*/
int floodfill(char *buf, int w, int h, int col_i, int row_i)
{
    if (col_i < 0 || col_i >= w || row_i < 0 || row_i >= h)
        return 0;
    int size = 1; // added for current cell, must be 1, not 0
    int idx = row_i *(w + 1) + col_i;
    if (buf[idx] != 'X')
        return 0; // gets udded in the recursion, dont do -1
    buf[idx] = 'V';
    size += floodfill(buf, w, h, col_i, row_i + 1);
    size += floodfill(buf, w, h, col_i, row_i - 1);
    size += floodfill(buf, w, h, col_i - 1, row_i);
    size += floodfill(buf, w, h, col_i + 1, row_i);
    return size;
}

int largest(char *buf, int w, int h)
{
    int size = 0, largest = 0;

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

void putnbr(int n)
{
    char c;
    if (n > 9)
        putnbr(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1); 
}

int main (int argc, char **argv)
{
    int fd, bytes, width, height, biggest;
    char *buf;
    struct  stat st;

    if (argc != 2)
        return (write(1, "\n", 1), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (write(1, "\n", 1), 1);
    if (fstat(fd, &st) < 0)
        return (close(fd), write(1, "\n", 1), 1);
    buf = malloc(st.st_size + 1);
    if (!buf)
        return (close(fd), write(1, "\n", 1), 1);
    bytes = read(fd, buf, st.st_size);
    if (!bytes)
        return (free(buf), close(fd),write(1, "\n", 1), 1);
    close(fd);
    buf[bytes] = '\0';
    if (validate_map(buf, &width, &height) == -1)
        return (free(buf), write(1, "\n", 1), 1);
    biggest = largest(buf, width, height);
    putnbr(biggest);
    write(1, "\n", 1);
    free(buf);
    return 0;
}