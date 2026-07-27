#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUF_SIZE 2000


// col len
int width_len(char *buf)
{
    int i = 0;
    while (buf[i] && buf[i] != '\n')
        i++;
    return i;
}

// validate 2d arr: rectangular, only X and . and \n, writes in *width and *height(rows, cols)
/* returns -1 on err, 0 on success; udated *width and *height vals */
int validate_map(char *buf, int *width, int *height)
{
    int h = 0, len = 0, i = 0;
    int w = width_len(buf);
    if (w == 0) return -1;
    
    while (buf[i])
    {
        if (buf[i] == '\n')
        {
            if (len != w) return -1;
            h++;
            len = 0;
        }
        else if (buf[i] != 'X' && buf[i] != '.') return -1;
        else
            len++;
        i++;
    }
    if (len != 0)
    {
        if (len != w) return -1;
        h++;
    }
    if (h == 0) return -1;
    *width = w;
    *height = h;
    return 0;
}

/* floodfill: recursivly from each cell to find a island and returns the size
returns: 0 on err, size of island on success: + num
*/
void floodfill(char *buf, int w, int h, int row_i, int col_i, char fill)
{
    if (row_i < 0 || row_i >= h || col_i < 0 || col_i >= w)
        return;
    
    int idx = row_i * (w + 1) + col_i;
    if (!buf[idx] || buf[idx] != 'X') return;
    buf[idx] = fill;
    floodfill(buf, w, h, row_i, col_i + 1, fill);
    floodfill(buf, w, h, row_i, col_i - 1, fill);
    floodfill(buf, w, h, row_i + 1, col_i, fill);
    floodfill(buf, w, h, row_i - 1, col_i, fill);
    return;
}

// count islands
int count_islands(char *buf, int w, int h)
{
    int count = 0;
    char fill = '1';

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int idx = i * (w + 1) + j;
            if (buf[idx] == 'X')
            {
                floodfill(buf, w, h, i, j, fill);
                count++;
                // if over 9 continue next ascii char
                    fill++;
            }
        }
    }
    return count;
}

static void put_nbr(int num)
{
    char c;
    if (num > 9)
        put_nbr(num/10);
    c = num % 10 + '0';
    write(1, &c, 1);
}

int main(int argc, char **argv)
{
    int width = 0, height = 0;
    if (argc != 2)
        return (printf("You need to add a file.txt to read from\n"), 1);
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (printf("Open file failed\n"), 1);
    
    // get reall buffer size:
    struct stat st;
    fstat(fd, &st);
    char *buf = malloc(st.st_size + 1);
    if (!buf)
        return (close(fd), printf("Malloc failed\n"), 1);
    int bytes = read(fd, buf, st.st_size);
    if (bytes == -1)
        return (close(fd), printf("Failed to read from file\n"), 1);
    close(fd);
    buf[bytes] = '\0';
    if (validate_map(buf, &width, &height) == -1)
        return(printf("Not valid map\n"), 1);
    
    int count = count_islands(buf, width, height);
    write(1, buf, bytes);
    write(1, "\n", 1);
    put_nbr(count);
    write(1, "\n", 1);
    free(buf);
    return 0;
}