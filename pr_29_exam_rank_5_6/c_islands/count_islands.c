#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int width_len(char *buf)
{
    int i = 0;
    while (buf[i] && buf[i] != '\n')
        i++;
    return i;
}

int validate_map(char *buf, int *width, int *height)
{
    int i = 0, len = 0, h= 0;
    int w = width_len(buf);

    if (w == 0) return 1; // remember
    while (buf[i])
    {
        if (buf[i] == '\n')
        {
            if (len != w)
                return (1);
            len = 0;
            h++;
        }
        else if (buf[i] != 'X' && buf[i] != '.')
            return (1);
        else
            len++;
        i++;
    }
    if (len != 0 && len != w) return (1); // remember
    if (len == w) h++;
    if (h == 0) return 1;
    *width = w;
    *height = h;
    return 0;
}

void put_num(int n)
{
    char c;

    if (n > 9)
        put_num(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
}

void floodfill(char *buf, int w, int h, int col_i, int row_i, char island)
{
    if (col_i < 0 || col_i >= w || row_i < 0 || row_i >= h)
        return;
    int idx = row_i * (w + 1) + col_i;
    if (buf[idx] != 'X') return;
    buf[idx] = island;
    floodfill(buf, w, h, col_i, row_i + 1, island);
    floodfill(buf, w, h, col_i, row_i - 1, island);
    floodfill(buf, w, h, col_i + 1, row_i, island);
    floodfill(buf, w, h, col_i - 1, row_i, island);
}

int count(char *buf, int w, int h)
{
    char island = '1';
    int n = 0;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int idx = i * (w + 1) + j;
            if (buf[idx] == 'X')
            {
                floodfill(buf, w, h, j, i, island);
                n++;
                if (island < '9')
                    island++;
            }
        }
    }
    return (n);
}

int main(int argc, char **argv)
{
    int fd, num, width = 0, height = 0;
    ssize_t bytes;
    char *buf;
    struct stat st;

    if (argc != 2)
        return (write(1, "Err\n", 4), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (write(1, "1Err\n", 5), 1);
    if (fstat(fd, &st) < 0)
        return (close(fd), write(1, "2Err\n", 5), 1);
    buf = malloc(st.st_size + 1);
    if (!buf)
        return (close(fd), write(1, "Err\n", 4), 1);
    bytes = read(fd, buf, st.st_size);
    close(fd);
    if (bytes < 1)
        return (write(1, "3Err\n", 5), 1);
    buf[bytes] = '\0';
    if (validate_map(buf, &width, & height) == 1)
        return (free(buf), write(1, "4Err\n", 5), 1);
    num = count(buf, width, height);
    write(1, buf, bytes);
    write(1, "\n", 1);
    put_num(num);
    write(1, "\n", 1);
    free(buf);
    return 0;
}