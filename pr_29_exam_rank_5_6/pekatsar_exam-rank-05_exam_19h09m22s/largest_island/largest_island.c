#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

// #define BUF_SIZE 2000

int width_len(char *buf) {
	int i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	return i;
}

// only X and .; each raw has same len, update width and height
int validate_map(char *buf, int *width, int *height) {
	int i = 0, len = 0, h = 0;
	int w = width_len(buf);
	if (w == 0) return -1;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			 if (w != len) return - 1;
			len = 0;
			h++;
		}
		else if (buf[i] != 'X' && buf[i] != '.') return -1;
		else len ++;
		i++;
	}
	if (len > 0)
	{
		if (len != w) return -1;
		h++;
	}
	if (h == 0) return -1;
	*width = w;
	*height = h;
	return 0;
}

int flood_fill(char *buf, int w, int h, int col_i, int raw_i) {
	int size = 1, idx;
	if (col_i < 0 || col_i >= w || raw_i < 0 || raw_i >= h)
		return 0;
	idx = raw_i * (w + 1) + col_i;
	if (buf[idx] != 'X') return 0;
	buf[idx] = 'V';
	size += flood_fill(buf, w, h, col_i, raw_i + 1);
	size += flood_fill(buf, w, h, col_i, raw_i - 1);
	size += flood_fill(buf, w, h, col_i + 1, raw_i);
	size += flood_fill(buf, w, h, col_i - 1, raw_i);
	return size;
}

int largest_island(char *buf, int w, int h) {
	int size = 0, largest = 0;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int idx = i * (w + 1) + j;
			if (buf[idx] == 'X') {
				size = flood_fill(buf, w, h, j, i);
				if (size > largest)
					largest = size;
			}
		}
	}
	return largest;
}

int flood_fill_count(char *buf, int w, int h, int col_i, int raw_i, char fill) {
	if (col_i < 0 || col_i >= w || raw_i < 0 || raw_i >= h)
		return 0;
	int idx = raw_i * (w + 1) + col_i;
	if (buf[idx] != 'X') return 0;
	buf[idx] = fill;
	flood_fill_count(buf, w, h, col_i, raw_i + 1, fill);
	flood_fill_count(buf, w, h, col_i, raw_i - 1, fill);
	flood_fill_count(buf, w, h, col_i + 1, raw_i, fill);
	flood_fill_count(buf, w, h, col_i - 1, raw_i, fill);
}

int count_island(char *buf, int w, int h) {
	char count = '0';
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int idx = i * (w + 1) + j;
			if (buf[idx] == 'X') {
				flood_fill_count(buf, w, h, j, i, count);
				++count;
			}
		}
	}
	return count;
}

void putnbr(int num)
{
	char c;
	if (num > 9)
		putnbr(num / 10);
	c = num % 10 + '0';
	write(1, &c, 1);
}

void print_msg()
{
	char *msg = "Map Error";
	int i = 0;

	while (msg[i])
	{
		write(1, &msg[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int main(int argc, char** argv) {
	int fd, bytes, width, height;
	struct stat st;
	char *buf;
	if (argc != 2) {
		// printf("Enter the file name\n");
		return 1;
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (print_msg(), 1);
	if(fstat(fd, &st) < 0)
	{
		return (close(fd), print_msg(), 1);
	}
	buf = malloc(st.st_size + 1);
	// buf = malloc(BUF_SIZE + 1);
	if (!buf)
		return (close(fd), print_msg(), 1);
	bytes = read(fd, buf, st.st_size);
	// bytes = read(fd, buf, BUF_SIZE);
	if (bytes <= 0)
		return (close(fd), free(buf), print_msg(), 1);
	buf[bytes] = '\0';
	close(fd);
	if (validate_map(buf, &width, &height) == -1) {
		return (free(buf),print_msg(), 1);
	}
	int biggest = largest_island(buf, width, height);
	putnbr(biggest);
	write(1, "\n", 1);
	free(buf);
	return 0;
}
