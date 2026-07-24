#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define DEAD_CH ' '
#define ALIVE_CH 'P'

/* step 1 get complete stdin str*/
static char* slurp_stdin(size_t *out_len)
{
	size_t cap = 4096;
	ssize_t n; // readline returns -1 on err
	size_t len = 0;
	char *buf = malloc(cap);

	if (!buf) return NULL;
	while(n = read(0, buf + len, cap - len) > 0)
	{
		len += (size_t)n;
		if (len == cap)
		{
			char *tmp = realloc(buf, cap *2);
			if (!tmp) return (free(buf), NULL);
			buf = tmp;
			cap *= 2;
		}
	}
	*out_len = len;
	return buf;
}
/* st 2*/
static void draw(unsigned char *grid, const char *mv_str, int w, int h, size_t len)
{
	int x = 0, y = 0, pen = 0;

	for (size_t i = 0; i < len; i++)
	{
		if (mv_str[i] == 'w' && y > 0)
			y--;
		else if (mv_str[i] == 's' && y < h -1)
			y++;
		else if (mv_str[i] == 'a' && x > 0)
			x--;
		else if (mv_str[i] == 'd' && x < w - 1)
			x++;
		else if (mv_str[i] == 'x')
			pen = !pen;
		if (pen)
			grid[y * w + x] = 1;
	}
}

/*
flow: 1.slurp stdin, 2. draw map, 3. steps, 4. print_borad
*/
int main(int argc, char **argv)
{
	char *mv_str; //st 1
	size_t len = 0; // st 1
	int w, h, iter; // st 2
	unsigned char *cur; // st 2
	
	if (argc != 4) return (putchar('\n'), 1); // st2
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	iter = atoi(argv[3]);
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int iter = atoi(argv[3]);
	
	if (w <= 0 || h <= 0) return; //still st 2
	mv_str = slurp_stdin(&len); // st 1
	// st2 draw
	cur = calloc((size_t)w * h, 1); //1 zeroed byte per cell
	if (!cur) return (free(mv_str), 1);
	draw(cur, mv_str, w, h, len);
	return 0;
}