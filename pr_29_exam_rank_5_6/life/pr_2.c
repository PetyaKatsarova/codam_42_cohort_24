#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define DEAD_CH ' '
#define ALIVE_CH 'P'

/* step 1 get complete stdin str*/
static char *get_cmds(size_t *cmds_len)
{
	size_t cap = 4096;
	size_t len = 0;
	char *str_cmds = malloc(cap);
	ssize_t n;

	if (!str_cmds) return NULL;
	while ((n = read(0, str_cmds + len, cap - len)) > 0) {
		if (n < 0)
		{
			// if (errno == EINTR) continue;
			free(str_cmds); return NULL;
		}
		len += (size_t)n;
		if (len == cap)
		{
			char *tmp = realloc(str_cmds, cap * 2);
			if (!tmp) return (free(str_cmds), NULL);
			cap *= 2;
			str_cmds = tmp;
		}
	}
	*cmds_len = len;
	return str_cmds;
}

static void draw_map(unsigned char *map, const char *str_cmds, int w, int h, size_t cmds_len) {
	int x = 0, y = 0, pen = 0;

	for (size_t i = 0; i < cmds_len; i++)
	{
		if (str_cmds[i] == 'w' && y > 0)
			y--;
		else if (str_cmds[i] == 's' && y < h - 1)
			y++;
		else if (str_cmds[i] == 'a' && x > 0)
			x--;
		else if (str_cmds[i] == 'd' && x < w - 1)
			x++;
		else if (str_cmds[i] == 'x')
			pen = !pen;
		if (pen)
			map[y * w + x] = 1;
	}
}

static int neighbours (const unsigned char *map, int w, int h, int x, int y)
{
	int n = 0;

	for (int step_y = -1; step_y <= 1; step_y++)
	{
		for (int step_x = -1; step_x <= 1; step_x++)
		{
			if (step_x == 0 && step_y == 0)
				continue;
			if (step_x + x < 0 || step_x + x >= w || step_y + y < 0 || step_y + y >=h )
				continue;
			n += map[(y + step_y) * w + (x + step_x)];
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
			next[y * w + x] = (n == 3 || (n == 2 && cur[y * w + x])); // if 3 neighb or 2 and cell alive(1)
		}
	}
}

static void print_board(const unsigned char *cur, int w, int h)
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
			putchar(cur[y * w + x] ? ALIVE_CH : DEAD_CH);
		putchar('\n');
	}
}

/*
flow: 1.slurp stdin, 2. draw map, 3. steps, 4. print_borad
*/
int main(int argc, char **argv)
{
	char 			*str_cmds;
	unsigned char 	*cur, *next, *temp;
	size_t			cmds_len;
	int				w, h, iter, i = 0;
	
	if (argc != 4)
		return (putchar('\n'), 1);
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	iter = atoi(argv[3]);
	if (w <= 0 || h <= 0 || iter < 0) return (1);
	cur = calloc((size_t)w * h, 1);
	next = calloc((size_t)w * h, 1);
	str_cmds = get_cmds(&cmds_len);
	if (!cur || !next || !str_cmds) return (free(str_cmds), free(cur), free(next), 1);
	draw_map(cur, str_cmds, w, h, cmds_len);
	while (i-- < iter)
	{
		step(cur, next, w, h);
		temp = cur; // not changed
		cur = next; // changed
		next = temp; // original, not changed
		i++;
	}
	print_board(cur, w, h);
	free(cur);
	free(next);
	free(str_cmds);
	return 0;
}