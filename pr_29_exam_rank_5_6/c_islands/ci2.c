#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// #define BUF_SIZE 2000
/*
given file path, open, read map, print/count islands: or give len biggest island:
allowed: write, open, malloc, free
*/
/*
plan: open file, read map, alloc mem for map
1. validate map(*buf, *width, *h): w = each line same, \n, only X or .
2.  flood_fill(*buf, w, h, col_i, row_i): size +=, buf[idx]='V'; for count islands: buf[idx] = fill;
3. biggest_island?/count: 2 loop: if buf[idx] == 'x' size = flood_fill();
*/
int width_len(char *buf)
{
    int i = 0;
    while (buf[i] && buf[i] != '\n')
        i++;
    return i;
}

static int validate_map(char *buf, int *width, int *height)
{
    int i = 0, len = 0, h = 0;
    int w = width_len(buf);
    if (w < 1)
        return -1;
    while (buf[i])
    {
        if (buf[i] == '\n')
        {
            if (w != len) return -1;
            len = 0;
            h++;
        }
        else if (buf[i] != 'X' && buf[i] != '.')    return -1;
        else
            len++;
        i++;
    }
    if (len > 0)
    {
        if (len != w) return -1;
        h++;
    }
    if (h < 1) return -1;
    *width = w;
    *height = h;
    return 0;
}

static int flood_fill(char *buf, int w, int h, int col_i, int raw_i)
{
    int size = 1;
    if (col_i < 0 || col_i >= w || raw_i < 0 || raw_i >= h)
        return 0;
    int idx = raw_i * (w + 1) + col_i; // + 1 for /n
    if (buf[idx] != 'X') return 0;
    buf[idx] = 'V';
    size += flood_fill(buf, w, h, col_i, raw_i + 1);
    size += flood_fill(buf, w, h, col_i, raw_i - 1);
    size += flood_fill(buf, w, h, col_i + 1, raw_i);
    size += flood_fill(buf, w, h, col_i - 1, raw_i);
    return size;
}

static int get_biggest(char *buf, int width, int height)
{
    int biggest = 0, size = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (buf[i * (width + 1) + j] == 'X')
            {
                size = flood_fill(buf, width, height, j, i);
                if (size > biggest)
                    biggest = size;
                }
        }
    }
    return biggest;
}

static void putnbr(int num)
{
    char c;
    if (num > 9) // reemeber !! not while
        putnbr(num / 10);
    c = num % 10 + '0';
    write (1, &c, 1);
}
// biggest island floodfill

int main(int argc, char **argv)
{
    int fd, bytes, width = 0, height = 0, biggest = 0;
    struct stat st;
    char *buf;


    if (argc != 2)
        return(write(1, "map err\n", 8), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return(write(1, "map err\n", 8), 1);
    if (fstat(fd, &st) < 0)
        return (close(fd), write(1, "\n", 1), 1);
    buf = malloc(st.st_size + 1); // fstat(fd, &st) < ); st.st_size
    if (!buf)
        return (close(fd), write(1, "err m\n", 6), 1);
    bytes = read(fd, buf, st.st_size); //rem not & but only buf!!!!
    if (bytes < 1)
        return (close(fd), free(buf),write(1, "err m\n", 6), 1);
    close(fd);
    buf[bytes] = '\0';
    if (validate_map(buf, &width, &height) == -1)
        return (free(buf), write(1, "err m\n", 6), 1);
    biggest = get_biggest(buf, width, height);
    if (biggest == -1)
        return (free(buf), write(1, "err m\n", 6), 1);
    // print_islands(buf, width, height);
    putnbr(biggest);
    write(1, "\n", 1);
    free(buf);
    return 0;
}