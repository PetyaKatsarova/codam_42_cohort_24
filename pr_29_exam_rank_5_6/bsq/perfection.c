#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
	char 	**grid;
	int		h;
	int		w;
	char	e;
	char	o;
	char	f;
} t_map;

static void free_board(char **grid, int rows)
{
	for (int i = 0; i < rows; i++)
		free(grid[i]);
	free(grid);
}

static void print_board(t_map *m)
{
	for (int i = 0; i < m->h; i++)
	{
		fputs(m->grid[i], stdout);
		fputs("\n", stdout);
	}
}

int read_header(t_map *m, FILE *fp)
{
	size_t	cap;
	ssize_t	len;
	char	*junk;

	if (fscanf(fp, "%d %c %c %c", &m->h, &m->e, &m->o, &m->f) != 4)
		return -1;
	if (m->e < 32 || m->e > 126 ||
		m->o < 32 || m->o > 126 ||
		m->f < 32 || m->f > 126) return -1;
	cap = 0;
	junk = NULL;
	len = getline(&junk, &cap, fp);
	if (len < 0)
		return (free(junk), -1);
	if (len != 1 || junk[0] != '\n') // remem!!
		return (free(junk), -1);
	free(junk);
	if (m->h < 1)
		return -1;
	if (m->e == m->o || m->e == m->f || m->o == m->f) return -1;
	return 0;
}

static int valid_line(t_map *m, char *line)
{
	for (int i = 0; i < m->w; i++)
	{
		if (line[i] != m->e && line[i] != m->o)
			return 0;
	}
	return 1;
}

int read_map(t_map *m, FILE *fp)
{
	char 	*line;
	size_t 	cap;
	ssize_t	len;

	m->grid = malloc((size_t)m->h * sizeof(char *));
	if (!m->grid) return -1;
	m->w = -1;
	for (int i = 0; i < m->h; i++)
	{
		line = NULL;
		cap = 0;
		len = getline(&line, &cap, fp);
		if (len == -1 || len < 1 || line[len - 1] != '\n')
			return (free(line), free_board(m->grid, i), -1);
		line[--len] = '\0'; //rmv n
		if (m->w == -1)
			m->w = (int)len;
		if (m->w != (int)len || m->w < 1 || !valid_line(m, line))
			return (free(line), free_board(m->grid, i), -1);
		m->grid[i] = line;
	}
	line = NULL;
	cap = 0;
	if (getline(&line, &cap, fp) >= 0)
		return (free(line), free_board(m->grid, m->h), -1);
	return 0;
}

static int get_lowest(t_map *m, int *dp, int i, int j)
{
	int v;
	if (m->grid[i][j] == m->o) return 0;
	if (i == 0 || j == 0) return 1;
	v = dp[(size_t)i * m->w + j - 1]; // left
	if (v > dp[(size_t)(i - 1) * m->w + j - 1])
		v = dp[(size_t)(i - 1) * m->w + j - 1];
	if (v > dp[(size_t)(i - 1) * m->w + j])
		v = dp[(size_t)(i - 1) * m->w + j];
	return v + 1;
}

static void fill_square(t_map *m, int bi, int bj, int best)
{
	for (int i = bi - best + 1; i <= bi; i++) // = or?
	{
		for (int j = bj - best + 1; j <= bj; j++)
		{
			m->grid[i][j] = m->f;
		}
	}
}

static int solve(t_map *m)
{
	int *dp;
	int bi = 0, bj = 0, best = 0;

	dp = calloc((size_t)m->h * (size_t)m->w, sizeof(int));
	if (!dp) return -1;
	for (int i = 0; i < m->h; i++)
	{
		for (int j = 0; j < m->w; j++)
		{
			int idx = (size_t)i * m->w + j;
			dp[idx] = get_lowest(m, dp, i, j);
			if (best < dp[idx])
			{
				best = dp[idx];
				bi = i;
				bj = j;
			}
		}
	}
	if (best > 0)
		fill_square(m, bi, bj, best);
	free(dp);
	return 0;
}

static int process(FILE *fp)
{
	t_map m;

	m.grid = NULL;
	m.h = 0;
	if (read_header(&m, fp) == -1) return -1;
	if (read_map(&m, fp) == -1)	return -1;
	if (solve(&m) == -1)
		return (free_board(m.grid, m.h), -1);
	print_board(&m);
	free_board(m.grid, m.h);
	return 0;
}

int main(int argc, char **argv)
{
	FILE *fp;
	if (argc == 1)
	{
		if (process(stdin) == -1)
			fprintf(stderr, "map error\n");
		return 0;
	}
	for (int i = 1; i < argc; i++)
	{
		fp = fopen(argv[i], "r");
		if (!fp)
			return 1;
		if (process(fp) == -1)
			fprintf(stderr, "map error\n");
		fclose(fp);
		if (argc > 2)
			fputs("\n", stdout);
	}
	return 0;
}