/*
** game_of_life
**
** usage: ./a.out <width> <height> <iterations>
**        the initial board is "drawn" by a pen driven from stdin:
**
**          w / a / s / d  -> move the pen up / left / down / right
**                            (moves that would leave the board are ignored)
**          x              -> toggle the pen (drawing <-> not drawing)
**
**        the pen starts at the top-left corner, in drawing mode; every cell
**        it stands on while drawing becomes alive.
**
** example: echo 'asdwd' | ./a.out 2 3 2
**              OO
**              OO
**              ..
*/

/*
char means "this is text," unsigned char means "this is a byte with a value I intend to do arithmetic on."

*/

/*
printf '          \n O   OOO  \n O     O  \n OOO  O   \n  O  OOO  \n          \n' > expected.txt
echo 'sdxssdswdxddddsxaadwxwdxwaa' | ./a.out 10 6 0 > got.txt
diff expected.txt got.txt && echo OK
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define DEAD_CH  ' '
#define ALIVE_CH 'O'

/* --- input ---
read the whole thing into memory in one gulp
*/

static char *slurp_stdin(size_t *out_len)
{
	size_t	cap = 4096;
	size_t	len = 0;
	char	*buf = malloc(cap);
	ssize_t	n;

	if (!buf)
		return (NULL);
	while ((n = read(0, buf + len, cap - len)) > 0)
	{
		len += (size_t)n;
		if (len == cap)
		{
			char *tmp = realloc(buf, cap * 2);
			if (!tmp)
			{
				free(buf);
				return (NULL);
			}
			buf = tmp;
			cap *= 2;
		}
	}
	*out_len = len;
	return (buf);
}

/* --- board building ---
** replays the pen commands and paints the initial board (generation 0).
** writes into the grid it is given -- main passes cur, so this fills cur.
**
** the pen starts at the top-left corner, lifted:
**   w a s d  move it up / left / down / right; a move that would leave
**            the board is ignored and the pen stays put
**   x        lowers or lifts the pen
** any other character is ignored.
**
** after every command the cell under the pen is marked alive if the pen
** is down -- including right after an x lowers it, so the pen leaves a
** mark where it touches down.
*/
static void	draw(unsigned char *g, int w, int h, const char *in, size_t len)
{
	int		x = 0;
	int		y = 0;
	int		pen = 0;

	for (size_t i = 0; i < len; i++)
	{
		if (in[i] == 'w' && y > 0)
			y--;
		else if (in[i] == 's' && y < h - 1)
			y++;
		else if (in[i] == 'a' && x > 0)
			x--;
		else if (in[i] == 'd' && x < w - 1)
			x++;
		else if (in[i] == 'x')
			pen = !pen;
		if (pen)
			g[y * w + x] = 1;
	}
}

/* --- one generation --- 
** counts how many of the 8 cells around (x, y) are alive.
**
** step_x / step_y walk the 3x3 block centred on (x, y):
**   - the (0, 0) offset is skipped, a cell is not its own neighbour
**   - offsets falling outside the board are skipped, so the edges are
**     hard walls and the board does not wrap around
**
** cells hold 1 for alive and 0 for dead, so neighbours can simply be
** summed. returns 0..8.
*/
static int	neighbours(const unsigned char *g, int w, int h, int x, int y)
{
	int	n = 0;
	int	step_x;
	int	step_y;

	for (step_y = -1; step_y <= 1; step_y++)
	{
		for (step_x = -1; step_x <= 1; step_x++)
		{
			if (step_x == 0 && step_y == 0)
				continue ;
			if (y + step_y < 0 || y + step_y >= h || x + step_x < 0 || x + step_x >= w)
				continue ;
			n += g[(y + step_y) * w + (x + step_x)];
		}
	}
	return (n);
}

static void	step(const unsigned char *cur, unsigned char *next, int w, int h)
{
	int	x;
	int	y;
	int	n;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			n = neighbours(cur, w, h, x, y);
			next[y * w + x] = (n == 3 || (n == 2 && cur[y * w + x]));
		}
	}
}

/* --- output --- */

static void	print_board(const unsigned char *g, int w, int h)
{
	int	x;
	int	y;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
			putchar(g[y * w + x] ? ALIVE_CH : DEAD_CH);
		putchar('\n');
	}
}

/* --- main --- */

int	main(int argc, char **argv)
{
	int				w;
	int				h;
	int				iter;
	size_t			len = 0;
	char			*in;
	unsigned char	*cur;
	unsigned char	*next;
	unsigned char	*tmp;

	if (argc != 4)
		return (write(2, "usage: prog width height iterations\n", 36), 1);
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	iter = atoi(argv[3]);
	if (w <= 0 || h <= 0 || iter < 0)
		return (1);
	cur = calloc((size_t)w * h, 1);
	next = calloc((size_t)w * h, 1);
	in = slurp_stdin(&len);
	if (!cur || !next || !in)
		return (free(cur), free(next), free(in), 1);
	draw(cur, w, h, in, len);
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
	free(in);
	return (0);
}