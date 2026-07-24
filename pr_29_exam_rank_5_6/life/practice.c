#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define DEAD_CH ' '
#define ALIVE_CH 'O'

int ft_atoi(char *val)
{
	int i = 0, res = 0;
	while (val[i])
	{
		res = res * 10 + (val[i] - '0');
		i++;
	}
	return res;
}

/* read all into mem in one gulp
return what was read from stdin, and update out_len
*/
static char* slurp_stdin(size_t *out_len)
{
	size_t cap = 4096; // buf capacity
	size_t len = 0; // bytes actually filled so far
	ssize_t n; // return of read: 0=EOF, -1 = error
	char *buf = malloc(cap); // first block

	if(!buf) return (NULL);
	while ((n = read(0, buf + len, cap - len)) > 0)
	{
		len += (size_t)n;
		if (len == cap)
		{
			char *tmp = realloc(buf, cap * 2);
			if (!tmp) return (free(buf), NULL);
			buf = tmp;
			cap *= 2;
		}
	}
	*out_len = len;
	return (buf);
}

/* board building */
static void draw(unsigned char *grid,  const char *move_str, int w, int h, size_t len)
{
	int x = 0, y = 0, pen = 0;

	for (size_t i = 0; i < len; i++)
	{
		if (move_str[i] == 'w' && y > 0) // up
			y--;
		else if (move_str[i] == 's' && y < h - 1) // down
			y++;
		else if (move_str[i] == 'a' && x > 0) //left
			x--;
		else if (move_str[i] == 'd' && x < w - 1)
			x++;
		else if (move_str[i] == 'x')
			pen = !pen;
		if (pen)
			grid[y * w + x] = 1;

	}
}

static int neighbours(const unsigned char *grid, int w, int h, int x, int y)
{
	int n = 0;

	for (int step_y = -1; step_y <= 1; step_y++)
	{
		for (int step_x = -1; step_x <= 1; step_x++)
		{
			if (step_x == 0 && step_y == 0)
				continue;
			if (y + step_y < 0 || y + step_y >= h || x + step_x < 0 || step_x + x >= w)
				continue;
			n += grid[(y + step_y) * w + (x + step_x)];
		}
	}
	return n;
}

static void step(const unsigned char *cur, unsigned char *next, int w, int h)
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int n = neighbours(cur, w, h, x, y);
			next[y * w + x] = (n == 3 || (n == 2 && cur[y * w + x]));
		}
	}
}

static void print_board(const unsigned char *grid, int w, int h)
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
			putchar(grid[y*w + x] ? ALIVE_CH : DEAD_CH);
		putchar('\n');
	}
}

int main(int argc, char **argv)
{
	int w, h, iter;
	size_t len = 0; // bytes read from stdin
	char *move_str; // the move str
	unsigned char *cur, *next, *tmp; // cur, next board, swap slot

	if (argc != 4) return (putchar('\n'), 1);
	w = ft_atoi(argv[1]);
	h = ft_atoi(argv[2]);
	iter = ft_atoi(argv[3]);

	if (w <= 0 || h <= 0) // our atoi doesnt work with sign:  || iter < 0
		return 1;
	cur = calloc((size_t)w * h, 1); // one zeroed byte per cell: 0=dead
	next = calloc((size_t)w * h, 1);
	move_str = slurp_stdin(&len); //read all from stdin, update real len
	if (!cur || !next || !move_str)
		return (free(cur), free(next), free(move_str), 1);
	draw(cur, move_str, w, h, len);
	while (iter-- > 0)
	{
		step(cur, next, w, h);
		tmp = cur;
		cur = next;
		next = tmp;
	}
	print_board(cur, w, h);
	free(cur);
	free(next);
	free(move_str);
	return 0;
}