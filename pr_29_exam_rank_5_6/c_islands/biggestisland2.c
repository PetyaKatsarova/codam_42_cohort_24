#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

/*
The number: ~131,000 cells
Frame size is exactly 64 bytes (pushq %rbp = 8, subq $48, %rsp, return address = 8). Against the default 8 MB stack:

8,388,608 / 64 = 131,072 frames

Measured threshold:

   map	cells				  result
360×360	129,600	         129600
365×365	133,225          segfault

Dead on 131,072.
*/
int width_len(char *buf)
{
    int i = 0;
    while (buf[i] != '\n' && buf[i] != '\0')
        i++;
    return i;
}

void putnbr(int n)
{
    char res;
    if (n > 9)
        putnbr(n / 10);
    res = (n % 10) + '0';
    write(1, &res, 1);
}

  void debug_char(int i, char c)
  {
      write(1, "i=", 2);
      putnbr(i);
      write(1, " val=", 5);
      putnbr((unsigned char)c);
      if (c == '\n')
          write(1, " NEWLINE\n", 9);
      else if (c == '\r')
          write(1, " CR\n", 4);
      else if (c == ' ')
          write(1, " SPACE\n", 7);
      else if (c != 'X' && c != '.')
          write(1, " BAD\n", 5);
      else
          write(1, "\n", 1);
  }


/*
1. validate: only X, . and \n; each line is == width
2. updated values of w and h of the map(rectangular)
3. return -1 on invalid, 0 on success
*/
int validate_map(char *buf, int *width, int *height)
{
    int i = 0, len = 0, h = 0;
    int w = width_len(buf);

    if (w == 0)
        return -1;
    while (buf[i])
    {
		//debug_char(i, buf[i]);
		//printf("*** %c\n", buf[i]);
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
    if (h == 0)
        return -1;
    *width = w;
    *height = h;
    return 0;
}

int flooldfill(char *buf, int w, int h, int col_i, int row_i)
{
    int size;

    if (col_i < 0 || col_i >= w || row_i < 0 || row_i >= h)
        return 0;
    size = 1;
    int idx = row_i * (w + 1) + col_i;
    if (buf[idx] != 'X') return 0;
    buf[idx] = 'V';
    size += flooldfill(buf, w, h, col_i, row_i + 1);
    size += flooldfill(buf, w, h, col_i, row_i - 1);
    size += flooldfill(buf, w, h, col_i - 1, row_i);
    size += flooldfill(buf, w, h, col_i + 1, row_i);
    return size;
}

int get_largest(char *buf, int h, int w)
{
    int size = 0, largest = 0;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int idx = i * (w + 1) + j;
            if (buf[idx] == 'X')
            {
                size = flooldfill(buf, w, h, j, i);
                if (size > largest)
                    largest = size;
            }
        }
    }
    return largest;
}

int main (int argc, char **argv)
{
    int fd, bytes, width, height;
    int biggest;
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
    if (bytes < 1)
        return (free(buf), close(fd),write(1, "\n", 1), 1);
    close(fd);
    buf[bytes] = '\0';
    if (validate_map(buf, &width, &height) == -1)
        return (free(buf), write(1, "Erorr Map\n", 10), 1);
    biggest = get_largest(buf, height, width);
    putnbr(biggest);
    write(1, "\n", 1);
    free(buf);
    return 0;
}