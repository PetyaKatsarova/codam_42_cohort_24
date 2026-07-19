#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

// get length of a line
int width_len(char *buf)
{
    int i = 0;
    while (buf[i] != '\n' && buf[i] != '\0')
        i++;
    return i;
}

// returns -1 on err, 0 on success
int validate_map(char *buf, int *width, int *height)
{
    int len = 0, h = 0, i = 0;
    int w = width_len(buf);

    while (buf[i] != '\0')
    {
        if (buf[i] == '\n')
        {
            if (len != w)
                return -1;
            len = 0;
            h++;
        }
        else if (buf[i] != 'X' && buf[i] != '.')
            return -1;
        else
            len++;
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

// returns size of island or 0 on no island
int floodfill(char *buf, int w, int h, int col_i, int row_i)
{
    int size = 1; // why 1 and not 0??
    if (row_i < 0 || row_i >= h || col_i < 0 || col_i >= w)
        return 0;
    int idx = row_i * (w + 1) + col_i;
    if (buf[idx] != 'X')
        return 0;
    buf[idx] = 'V';
    size += floodfill(buf, w, h, col_i, row_i + 1);
    size += floodfill(buf, w, h, col_i, row_i - 1);
    size += floodfill(buf, w, h, col_i - 1, row_i);
    size += floodfill(buf, w, h, col_i + 1, row_i);
    return size;
}

int largest_island(char *buf, int width, int height)
{
    int size = 0, largest = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int idx = i * (width + 1) + j;
            if (buf[idx] == 'X')
            {
                size = floodfill(buf, width, height, j, i);
                if (size > largest)
                    largest = size;
            }
        }
    }
    return largest;
}

void putnbr(int n)
{
    char pr;
    if (n > 9)
        putnbr(n/10);
    pr = n % 10 + '0';
    write (1, &pr, 1);
}

int main(int argc, char **argv)
{
    int fd, bytes, w, h, largest;
    char *buf;
    struct stat st;

    if (argc != 2)
        return (write(1, "\n", 1), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (write(1, "\n", 1), 1);
    fstat(fd, &st);
    buf = malloc(st.st_size + 1);
    if (!buf)
        return (close(fd), write(1, "\n", 1), 1);
    bytes = read(fd, buf, st.st_size);
    if (bytes < 0)
        return (free(buf), close(fd), write(1, "\n", 1), 1);
    close(fd);
    buf[bytes] = '\0'; // do i add + 1?
    if (validate_map(buf, &w, &h) == -1)
        return (free(buf), write(1, "\n", 1), 1);
    largest = largest_island(buf, w, h);
    putnbr(largest);
    free(buf);
    write(1, "\n", 1);
    return 0;
}