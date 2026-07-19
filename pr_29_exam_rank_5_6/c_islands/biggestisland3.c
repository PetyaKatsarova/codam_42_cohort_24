#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int width_len(char* buf)
{
	int i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	return i;
}

// return -1 on error(each line must be same len, only X or .), 0 on success
// updates real map width/height 
int validate_map(char *buf, int *width, int *height)
{
	int i = 0, len = 0, h = 0;
	int w = width_len(buf);
	if (w == 0)
		return -1;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			if (w != len)
				return (write(1, "\n", 1), -1);
			len = 0;
			h++;
		}
		else if (buf[i] != 'X' && buf[i] != '.')
			return (write(1, "\n", 1), -1);
		else
			len++;
		i++;
	}
	if (len > 0)
	{
		if (len != w)
			return (write(1, "\n", 1), -1);
		h++;
	}
	if (h == 0)
		return (write(1, "\n", 1), -1);
	*width = w;
	*height = h;
	return 0;
}

// return size of island or 0
int flood_fill(char *buf, int w, int h, int col_i, int raw_i)
{
	int size = 1; // must be one: per cell
	if (col_i < 0 || col_i >= w || raw_i < 0 || raw_i >= h)
		return 0;
	int idx = raw_i * (w + 1) + col_i;
	if (buf[idx] != 'X')
		return 0;
	buf[idx] = 'V'; // remember!! otherwise endless loop
	size += flood_fill(buf, w, h, col_i, raw_i + 1); // remember!! +=
	size += flood_fill(buf, w, h, col_i, raw_i - 1);
	size += flood_fill(buf, w, h, col_i + 1, raw_i);
	size += flood_fill(buf, w, h, col_i - 1, raw_i);
	return size;
}

int biggest_island(char *buf, int w, int h)
{
	int size = 0, largest = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int idx = i * (w + 1) + j;
			if (buf[idx] == 'X')
			{
				size = flood_fill(buf, w, h, j, i);
				if (size > largest) // rmemeber!! <>
					largest = size;
			}
		}
	}
	return largest;
}

void put_nbr(int n)
{
	char c;
	if (n > 9) // recursion => if, not white
		put_nbr(n / 10);
	c = n % 10 + '0'; // !! remember + '0'
	write(1, &c, 1);
}

int main(int argc, char **argv)
{
	int fd, bytes, width = 0, height = 0, biggest = 0;
	struct stat st;
	char *buf;

	if (argc != 2)
		return (write(1, "\n", 1), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 1)
		return (write(1, "\n", 1), 1);
	if (fstat(fd, &st) < 0)
		return (close(fd), write(1, "\n", 1), 1);
	buf = malloc(st.st_size  + 1); // remember !! same
	if (!buf)
		return (close(fd), write(1, "\n", 1), 1);
	bytes = read(fd, buf, st.st_size); // !!NB: remember:not &buf buf only buf!!
	if (bytes < 1)
		return (close(fd), free(buf), write(1, "\n", 1), 1);
	close(fd);
	buf[bytes] = '\0';
	if (validate_map(buf, &width, &height) == -1)
		return (free(buf), write(1, "\n", 1), 1);
	biggest = biggest_island(buf, width, height);
	free(buf);
	put_nbr(biggest);
	write(1, "\n", 1);
	return 0;
}