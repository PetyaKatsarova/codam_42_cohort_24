#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// open, fstat, malloc, read
char *read_file(char *path, int *map_len)
{
	int fd;
	struct stat st;
	char *buf;

	fd = open(path, O_RDONLY);
	if (fd < 0) return NULL;
	if (fstat(fd, &st) < 0)	return(close(fd), NULL);
	buf = malloc(st.st_size + 1);
	if (!buf) return (close(fd), NULL);
	*map_len = read(fd, buf, st.st_size);
	if (*map_len <= 0) return (free(buf), close(fd), NULL);
	close(fd);
	buf[*map_len] = '\0';
	return (buf);
}

int width_len(char *buf)
{
	int i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	return i;
}

// width each line is same, only X,. or \n; update widht and h
int validate_map(char *buf, int *width, int *height)
{
	int i = 0, h = 0, len= 0;

	int w = width_len(buf);
	if (w == 0) return (-1);

	while(buf[i])
	{
		if (buf[i] == '\n')
		{
			if (len != w) return (-1);
			len = 0;
			h++;
		}
		else if (buf[i] != 'X' && buf[i] != '.') return (-1);
		else
			len++;
		i++;
	}
	if (len != w) return (-1);
	if (h == 0) return (-1);
	*width = w;
	*height = h;
}

void	print_msg(void)
{
	char	*msg;
	int		i;

	msg = "Map Error";
	i = 0;
	while (msg[i])
	{
		write(1, &msg[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int main (int argc, char **argv)
{
	int map_len, width, height;
	int		*stack;
	char	*buf;
	struct stat st;

	if (argc != 2)
		return (print_msg(), 1);
	buf = read_file(argv[1], &map_len);
	if (!buf) return (print_msg(), 1);
	if (validate_map(buf, &width, &height) == -1)
		return (free(buf), print_msg(), 1);
	stack = malloc(width * height * sizeof(int));
	if (!stack)
		return (free(buf), print_msg(), 1);
	

	return 0;

}