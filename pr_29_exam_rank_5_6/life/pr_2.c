#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define DEAD_CH ' '
#define ALIVE_CH 'P'

/* fun fact: ^@ is null byte*0x00*, real space ' '90x20 */
/*
int n = 0;                          // neighbour count
for (int i = -1; i <= 1; i++)       // row offset: above(-1), same(0), below(+1)
  for (int j = -1; j <= 1; j++)     // col offset: left(-1), same(0), right(+1)
    if (j == 0 && i == 0) continue; // skip the cell itself (0,0 offset)
    if (y+i<0 || y+i>=h || x+j<0 || x+j>=w) continue; // skip out-of-bounds
    n += g[(y + i) * w + (x + j)];  // add neighbour's value (1 if alive)
return n;
*/
char* get_cmds(size_t *cmds_len)
{
	size_t cap = 4096, l = 0;
	char* buf = malloc(cap);
	ssize_t bytes;

	if (!buf) return NULL;
	while ((bytes = read(0, buf+l, cap-l)) > 0)
	{
		l += (size_t)bytes;
		if (l == cap)
		{
			char *tmp = realloc(buf, cap * 2);
			if (!tmp) return (free(buf), NULL); // rem freebuf!!
			buf = tmp;
			cap *= 2;
		}
	}
	if (bytes < 0) // read err rem!!
		return (free(buf), NULL);
	buf[l] = '\0'; // rem!! again!!!
	*cmds_len = l;
	return buf;
}

static void draw_board(char *cur, char *cmds, int w, int h, size_t cmds_len)
{
	int pen = 0, x = 0, y = 0;

	for (size_t i = 0; i < cmds_len; i++)
	{
		if (cmds[i] == 'w' && y > 0)
			y--;
		else if (cmds[i] == 's' && y < h - 1)
			y++;
		else if (cmds[i] == 'a' && x > 0)
			x--;
		else if (cmds[i] == 'd' && x < w - 1)
			x++;
		else if (cmds[i] == 'x')
			pen = !pen;
		if (pen)
			cur[y*w+x] = 1;
	}
}
// x, y curr pos, + j + j: neighbrs: -1, 0, 1
static int neighbours(char *curr, int w, int h, int x, int y)
{
	int n = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) // self, no n
				continue;
			if (y + i < 0 || y + i >= h || j + x < 0 || j + x >= w) continue;
			n += curr[(y+i)*w + (x + j)];
		}
	}
	return n;
}
// for each cell, find neighbrs, write in next[idx] = 1 || 0: depending on how many ns
static void step(char *cur, char *next, int w, int h)
{
	int n;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			n = neighbours(cur, w, h, j, i);
			next[i*w+j] = (n == 3 || (n == 2 && cur[i*w+j]));
		}
	}
}

static void print_board(char *cur, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			putchar(cur[i*w+j] ? ALIVE_CH : DEAD_CH); // !!remem alive and dead!!
		}
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
	// remem checks!!
	if (w <= 0 || h <=0 || iter < 0) return 1;
	cur = calloc(w * h + 1, 1);
	next = calloc(w * h + 1, 1);
	cmds = get_cmds(&cmds_len);
	if (!cur || !next || ! cmds)
		return(free(cur), free(cmds), free(next), 1);
	//printf("cmds: %s\n", cmds); //for debug
	draw_board(cur, cmds, w, h, cmds_len);
	while (iter-- > 0)
	{
		step(cur, next, w, h); // on each step update from old
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