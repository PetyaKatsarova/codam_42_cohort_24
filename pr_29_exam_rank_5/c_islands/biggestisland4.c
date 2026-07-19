#include <fcntl.h>
#include <sys/stat.h>

int width_len(char *buf)
{
	int i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	return i;
}
// update widht and heigth real values
// check if each line has same widht and only X and .
// return -1 on not valid
int validate_map(char *buf, int *width, int *height)
{
	int h = 0, i = 0, len = 0;
	int w = width_len(buf);

	if (w == 0)
		return -1;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			if (w != len)
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
	width = w;
	height = h;
	return 0;
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
        return (free(buf), write(1, "\n", 1), 1);
    biggest = get_largest(buf, height, width);
    putnbr(biggest);
    write(1, "\n", 1);
    free(buf);
    return 0;
}