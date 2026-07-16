#include "life.h"

/*
GAME OF LIFE
============
how to play/test:
================
can create input.txt file with: 
dxxsdxxsaaxxdxxdxx
./ 10 10 1 < input.txt > result1.txt
./ 10 10 2 < input.txt > result2.txt
./ 10 10 3 < input.txt > result3.txt
./ 10 10 4 < input.txt > result4.txt
./ 10 10 5 < input.txt > result5.txt

Notice that the if (draw) check runs after every accepted command, including x itself. So:

first x: pen turns ON → immediately draws a 0 at the current cursor position
second x: pen turns OFF → nothing drawn

So xx = "stamp one cell here, then keep the pen up". That way moving afterwards doesn't leave a trail.
=====================

DESCRIPTION
    A minimal implementation of Conway's Game of Life in C.
    The board is drawn interactively via stdin, then the simulation
    runs a fixed number of generations and prints the final state.

USAGE
    ./life <width> <height> <iterations>

    All three arguments must be positive integers.
    Example: ./life 20 10 5

INPUT (read from stdin until EOF)
    w   move cursor up
    a   move cursor left
    s   move cursor down
    d   move cursor right
    x   toggle pen on/off (pen down = cells are drawn while moving)

    While the pen is active, every accepted command marks the current
    cell as alive ('0'). All other characters are ignored.
    End input with Ctrl+D, or pipe commands:
        echo "sxdd" | ./life 5 5 1

RULES
    Standard Conway rules, non-wrapping borders:
    - A live cell with 2 or 3 live neighbors survives
    - A dead cell with exactly 3 live neighbors becomes alive
    - All other cells die or stay dead

OUTPUT
    The final board printed to stdout, one row per line.
    Live cells are '0', dead cells are spaces.

RETURN VALUE
    0 on success, 1 on invalid arguments or allocation failure.

typedef struct life
{
    char    **board;
    int     w;
    int     h;
} t_life;
*/

char	**alloc_board(int w, int h)
{
	char	**board;
	int		i;
	int		j;

	board = calloc(h, sizeof(char *));
	if (!board)
		return (NULL);
	i = 0;
	while (i < h)
	{
		board[i] = malloc(w);
		if (!board[i])
		{
			while (--i >= 0)
				free(board[i]);
			free(board);
			return (NULL);
		}
		j = 0;
		while (j < w)
			board[i][j++] = ' ';
		i++;
	}
	return (board);
}

void	free_board(char **board, int h)
{
	int	i;

	i = 0;
	while (i < h)
		free(board[i++]);
	free(board);
}

void	fill_board(t_life *g)
{
	char	c;
	int		row;
	int		col;
	int		draw;

	row = 0;
	col = 0;
	draw = 0;
	while (read(0, &c, 1) == 1)
	{
		if (c == 'w' && row > 0)
			row--;
		else if (c == 's' && row < g->h - 1)
			row++;
		else if (c == 'a' && col > 0)
			col--;
		else if (c == 'd' && col < g->w - 1)
			col++;
		else if (c == 'x')
			draw = !draw;
		else
			continue ;
		if (draw)
			g->board[row][col] = '0';
	}
}

int	count_neighbors(t_life *g, int row, int col)
{
	int	count;
	int	dr;
	int	dc;
	int	nr;
	int	nc;

	count = 0;
	dr = -1;
	while (dr <= 1)
	{
		dc = -1;
		while (dc <= 1)
		{
			if (dr != 0 || dc != 0)
			{
				nr = row + dr;
				nc = col + dc;
				if (nr >= 0 && nr < g->h && nc >= 0 && nc < g->w)
					if (g->board[nr][nc] == '0')
						count++;
			}
			dc++;
		}
		dr++;
	}
	return (count);
}

int	next_gen(t_life *g)
{
	char	**next;
	int		neighbors;
	int		i;
	int		j;

	next = alloc_board(g->w, g->h);
	if (!next)
		return (-1);
	i = 0;
	while (i < g->h)
	{
		j = 0;
		while (j < g->w)
		{
			neighbors = count_neighbors(g, i, j);
			if (g->board[i][j] == '0')
				next[i][j] = (neighbors == 2 || neighbors == 3) ? '0' : ' ';
			else
				next[i][j] = (neighbors == 3) ? '0' : ' ';
			j++;
		}
		i++;
	}
	free_board(g->board, g->h);
	g->board = next;
	return (0);
}

void	printboard(t_life *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->h)
	{
		j = 0;
		while (j < g->w)
			putchar(g->board[i][j++]);
		putchar('\n');
		i++;
	}
}

int	main(int arc, char *argv[])
{
	t_life	g;
	int		iter;
	int		i;

	if (arc != 4)
		return (1);
	g.w = atoi(argv[1]);
	g.h = atoi(argv[2]);
	iter = atoi(argv[3]);
	if (g.h <= 0 || g.w <= 0 || iter <= 0)
		return (1);
	g.board = alloc_board(g.w, g.h);
	if (!g.board)
		return (1);
	fill_board(&g);
	i = 0;
	while (i++ < iter)
	{
		if (next_gen(&g) == -1)
		{
			free_board(g.board, g.h);
			return (1);
		}
	}
	printboard(&g);
	free_board(g.board, g.h);
	return (0);
}