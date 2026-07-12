#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF 2000
//https://github.com/muta-pro/C---exam/blob/main/Exam_05/largestIsland/largest_island.c

/* Returns the length of the first line in buf (up to '\n' or '\0'),
 used as the reference width every map row must match.
 */
int	width_len(char *buf)
{
	int	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	return (i);
}

/* Validates that buf is a rectangular map of only 'X'/'.' characters
 (every row the same width); writes the map's width/height out via
 *width and *height. Returns 1 if valid, 0 otherwise.
 */
int	parse_map(char *buf, int *width, int *height)
{
	int	i = 0;
	int	len = 0;
	int	h = 0;
	int w = width_len(buf);

	if (w == 0)
		return (0);
	while (buf[i]) // validate line: only X, . or \n and each line==size
	{
		if (buf[i] == '\n')
		{
			if (len != w)
				return (0);
			h++;
			len = 0;
		}
		else if (buf[i] != 'X' && buf[i] != '.')
			return (0);
		else
			len++;
		i++;
	}
	if (len != 0) // last row check
	{
		if (len != w)
			return (0);
		h++;
	}
	if (h == 0) // if no row
		return (0);
	*width = w;
	*height = h;
	return (1);
}

/* Recursively floods outward from (row, col), marking every
 connected 'X' as visited ('V'). Returns the total island size.
 */
int	floodfill(char *buf, int row, int col, int w, int h)
{
	int	size;
	int	idx;

	if (row < 0 || row >= h || col < 0 || col >= w)
		return (0);
	size = 1;
	idx = row * (w + 1) + col;
	if (buf[idx] != 'X')
		return (0);
	buf[idx] = 'V';
	size += floodfill(buf, row, col + 1, w, h);
	size += floodfill(buf, row, col - 1, w, h);
	size += floodfill(buf, row + 1, col, w, h);
	size += floodfill(buf, row - 1, col, w, h);
	return (size);
}

/* Scans every cell in the map; for each unvisited 'X', flood-fills
 it to measure that island's size, and tracks the biggest one seen.
 */
int	largest_island(char *buf, int w, int h)
{
	int	row;
	int	col;
	int	largest;
	int	size;
	int	idx;

	largest = 0;
	row = 0;
	while (row < h)
	{
		col = 0;
		while (col < w)
		{
			idx = row * (w + 1) + col;
			if (buf[idx] == 'X')
			{
				size = floodfill(buf, row, col, w, h);
				if (size > largest)
					largest = size;
			}
			col++;
		}
		row++;
	}
	return (largest);
	}

/* Writes the decimal representation of a non-negative int directly
 to stdout, one digit at a time (no printf allowed on this exam).
 */
void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	char c = (n % 10) + '0';
	write(1, &c, 1);
}

/* Entry point: reads argv[1] as a map file, validates it, finds the
 largest connected island of 'X's, and prints its size (or an empty
 line on any error). Frees all resources on every exit path.
 */
int	main(int argc, char *argv[])
{
	int		fd;
	int		bytes;
	char	*buf;
	int		largest;
	int		w;
	int		h;

	if (argc != 2)
		return (write(1, "\n", 1), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write(1, "\n", 1), 1);
	buf = malloc(BUF);
	if (!buf)
		return (close(fd), write(1, "\n", 1), 1);
	bytes = read(fd, buf, BUF - 1);
	if (bytes < 1)
		return (close(fd), free(buf), write(1, "\n", 1), 1);
	close(fd);
	buf[bytes] = '\0';
	if (!parse_map(buf, &w, &h))
		return (free(buf), write(1, "\n", 1), 1);
	largest = largest_island(buf, w, h);
	ft_putnbr(largest);
	write(1, "\n", 1);
	free(buf);
	return (0);
}