#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
plan:
main: calloc cur, next; step->tmp=cur,cur=n, n= tmp
getstr()
draw_map(cur, cmds): wsadx
neighbours(x=-1;  x<=1: loop): return n
step(cur, next)next[i*w + j] = (n==3 ||(n==2 && cur[..]))
printboard
*/
#define DEAD_CH ' '
#define ALIVE_CH 'P'

static char *get_cmds(size_t *str_len)
{
	size_t l = 0, cap = 4096; // should cap be int?
	ssize_t bytes = 0;
	char *buf;

	buf = malloc(cap + 1);
	if (!buf) return NULL;
	while ((bytes = read(0, buf + l, cap - l)) > 0)
	{
		l += (size_t)bytes;
		if (l == cap)
		{
			char *tmp = realloc(buf, cap * 2);
			if (!tmp) return (free(buf), NULL);
			buf = tmp;
			cap *= 2;
		}
	}
	if (bytes < 0) return(free(buf), NULL);
	buf[l] = '\0';
	*str_len = l;
	return buf;
}

static void draw_map(char *cur, char *cmds, int w, int h, size_t cmds_len)
{
	int x = 0, y = 0, pen = 0;

	for (size_t i = 0; i < cmds_len; i++)
	{
		if (cmds[i] == 'w' && y - 1 >= 0)
			y--;
		else if (cmds[i] == 's' && y + 1 < h)
			y++;
		else if (cmds[i] == 'a' && x - 1 >= 0)
			x--;
		else if (cmds[i] == 'd' && x + 1 < w)
			x++;
		else if (cmds[i] == 'x')
			pen = !pen;
		if (pen)
			cur[(size_t)y*w + x] = 1;	
	}
}

static int neighbours(char *cur, int w, int h, int x, int y)
{
	int n = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue;
			if (i + y < 0 || i + y >= h || j + x < 0 || j + x >= w) continue;
			if (cur[(size_t)(i + y) * w + j + x])
				n++;
		}
	}
	return n;
}

static void step(char *cur, char *next, int w, int h)
{
	int n = 0;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			n = neighbours(cur, w, h, j, i);
			next[(size_t)i * w + j] = (n == 3 || (n == 2 && cur[(size_t)i * w + j]));
		}
	}
}

static void print_board(char *cur, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			putchar(cur[(size_t)i * w + j] ? ALIVE_CH : DEAD_CH);
		putchar('\n');
	}
}

//./life width height iterations: remem: 8 vars!!
int main(int argc, char **argv)
{
	char *cmds;
	char *cur, *next, *tmp = NULL;
	size_t cmds_len = 0;
	int w, h, iter;

	(void)iter;
	(void)tmp;
	if (argc != 4) return 1;
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	iter = atoi(argv[3]);
	cur = calloc((size_t)w * h + 1, 1);
	next = calloc((size_t)w * h + 1, 1);
	cmds = get_cmds(&cmds_len);
	if (!cur || !next || !cmds)
		return (free(cur), free(next), free(cmds), 1);
	draw_map(cur, cmds, w, h, cmds_len);
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
	free(cmds);
	return 0;
}