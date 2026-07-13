#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUF	2000

// returns arr len: of first inner arr, till the \n
int width_len(char *buf)
{
	int i = 0;
	while(buf[i] && buf[i] != '\n')
		i++;
	return i;
}

// returns 1 if correct, 0 on parse err: expect rectangular map of only 'X', '.' or '\n'
// updates width and heigh
int parse_map(char *buf, int *width, int *height)
{
	int i = 0;
	int len = 0;
	int h = 0;
	int w = width_len(buf);

	if (w == 0)
		return 0;
	while (buf[i]) {
		if (buf[i] == '\n') { // end of inner arr
			if (len != w) return 0;
			h++;
			len = 0;
		}
		else if (buf[i] != 'X' && buf[i] != '.') return 0;
		else
			len++;
		i++;
	}
	if (len != 0)
	{
		if (len != w) return 0;
		h++;
	}
	if (h == 0) return 0;
	*width = w;
	*height = h;
	return 1;
}
/*
Think of a grid of letters like a big wall of text, but stored in computer memory as one long straight line of boxes (not a
  real 2D grid).
  Example, a 3-row, 4-column grid:
  Row 0: A B C D
  Row 1: E F G H
  Row 2: I J K L
  Each row also has an invisible \n at the end, so each row actually takes up 5 boxes (w=4, +1 for the \n), not 4.
  In memory, it's all squished into one long line:
  A B C D \n E F G H \n I J K L \n
  0 1 2 3 4  5 6 7 8 9  ...
  Now say you want row 1, col 2 — that's the letter G.

  - First, skip whole rows to get to the start of row 1. Each row takes 5 boxes, and you want to skip 1 row, so: 1 * 5 = 5.
  Box number 5 is indeed the start of row 1 (E).
  - Now you're standing at the start of row 1, but you want col 2, not col 0. So walk forward 2 more boxes: 5 + 2 = 7. Box
  number 7 is G
*/
int floodfill(char *buf, int row_i, int col_i, int w, int h)
{
	int size = 1, i;

	if (row_i < 0 || row_i >= h || col_i < 0 || col_i >= w) return 0;

	i = row_i * (w + 1) + col_i; // starting position
	if (buf[i] != 'X') return 0;
	buf[i] = 'V'; //change x to v: counted
	size += floodfill(buf, row_i, col_i + 1, w, h);
	size += floodfill(buf, row_i, col_i - 1, w, h);
	size += floodfill(buf, row_i - 1, col_i, w, h);
	size += floodfill(buf, row_i + 1, col_i, w, h);
	return size;
}

/*
flood fill each unvisited cell 'X' to count islands, starting from 0,0
*/
int largest_island(char *buf, int w, int h)
{
	int col, size, i;

	int row = 0; // outer arr
	int largest = 0;
	while (row < h)
	{
		col = 0;
		while (col < w)
		{
			i = row * (w + 1) + col;
			if (buf[i] == 'X')
			{
				size = floodfill(buf, row, col, w, h);
				if (size > largest)
					largest = size;
			}
			col++;
		}
		row++;
	}
	return largest;
}

/*
Recursion doesn't skip forward — each call pauses, it doesn't disappear
  When putnbr(123) runs and hits putnbr(n / 10), that current call does
  not finish. It's paused mid-execution, waiting for the recursive call
  to return, with its own local variables (n = 123) frozen in place.
  So calling putnbr(123) creates a stack of paused calls:
  putnbr(123)   -- paused, waiting, n=123
    putnbr(12)  -- paused, waiting, n=12
      putnbr(1) -- n=1, condition false, doesn't recurse further
*/
void putnbr(int n)
{
	if (n > 9)
		putnbr(n / 10);
	char c = (n % 10) + '0';
	write(1, &c, 1);
}

int main(int argc, char **argv)
{
	int fd, bytes, w, h, largest;
	char *buf;

	if (argc != 2)
		return (write(1, "\n", 1), 1);
	fd = open(argv[1], O_RDONLY);
	buf = malloc(BUF);
	if (!buf)
		return(close(fd), write(1, "\n", 1), 1);
	bytes = read(fd, buf, BUF-1);
	if (bytes < 0)
		return(close(fd), write(1, "\n", 1), 1);
	close(fd);
	buf[bytes] = '\0';
	if (!parse_map(buf, &w, &h))
		return (free(buf), write(1, "\n", 1), 1);
	largest = largest_island(buf, w, h);
	printf("Largest island is: %d\n", largest);
	free(buf);
	return 0;
}