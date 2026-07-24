#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int width_len(char *buf)
{
    int i = 0;
    while (buf[i] && buf[i] != '\n')
        i++;
    return (i);
}

int validate_map(char *buf, int *width, int *height)
{
    int i = 0, len = 0, h = 0;
    int w = width_len(buf);

    if (w == 0) return (1);
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
    if (len != 0 && len != w) return (1);
    if (len == w) h++;
    if (h == 0) return (1);                 // FIX: reject a map with zero rows
    *width = w;
    *height = h;
    return (0);
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

void put_num(int n)                         // FIX: new helper, prints an int as digits
{
    char c;

    if (n >= 10)
        put_num(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
}

int count(char *buf, int w, int h)
{
    char island = '1';
    int n = 0;                              // FIX: count separately from the marker char

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int idx = i * (w + 1) + j;
            if (buf[idx] == 'X')
            {
                floodfill(buf, w, h, j, i, island);
                n++;                        // FIX: increment the real counter
                if (island < '9')           // FIX: don't walk past '9' into ':' ';' '<'
                    island++;
            }
        }
    }
    return (n);                             // FIX: was returning the marker char, off by one
}

int main(int argc, char **argv)
{
    int fd, num, width = 0, height = 0;
    ssize_t bytes;                          // FIX: read() returns ssize_t, not int
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
    if (!buf)                               // FIX: malloc return was unchecked
        return (close(fd), write(1, "5Err\n", 5), 1);
    bytes = read(fd, buf, st.st_size);
    close(fd);                              // FIX: close once, before branching
    if (bytes < 1)
        return (free(buf), write(1, "3Err\n", 5), 1);   // FIX: buf was leaked here
    buf[bytes] = '\0';
    if (validate_map(buf, &width, &height) == 1)
        return (free(buf), write(1, "4Err\n", 5), 1);
    num = count(buf, width, height);
    write(1, buf, bytes);
    write(1, "\n", 1);
    put_num(num);                           // FIX: was write(1, &num, 1) — raw int byte
    write(1, "\n", 1);                      // FIX: terminate the output line
    free(buf);
    return (0);
}