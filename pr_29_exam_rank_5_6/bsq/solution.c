#include <stdio.h>
#include <stdlib.h>

  /* ** DYNAMIC PROGRAMMING **
    dp[i][j] = size of the largest all-empty square whose bottom-right
    corner is at (i, j). Classic "maximal square" DP:
      obstacle          -> dp[i][j] = 0
      first row/col     -> dp[i][j] = 1
      otherwise         -> 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
    We only update best on strict '>' so scanning top-to-bottom,
    left-to-right naturally gives the topmost-then-leftmost tie-break
  */

typedef struct s_map
{
	int		n, w;
	char	e, o, f;
	char	**grid;
}	t_map;

void	free_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(grid[i++]);
	free(grid);
}

/* fscan read first line, update map vals, validate, return -1 on err, 0 on success*/
int	read_header(FILE *fp, t_map *m)
{
	char	*rest;
	size_t	cap;

	if (fscanf(fp, "%d %c %c %c", &m->n, &m->e, &m->o, &m->f) != 4)
		return (-1);
	rest = NULL;
	cap = 0;
	if (getline(&rest, &cap, fp) == -1)
		return (free(rest), -1);
	free(rest);
	if (m->n < 1)
		return (-1);
	if (m->e == m->o || m->e == m->f || m->o == m->f)
		return (-1);
	return (0);
}

static int	valid_line(char *line, t_map *m)
{
	int	j;

	j = 0;
	while (j < m->w)
	{
		if (line[j] != m->e && line[j] != m->o)   /* body = empty | obstacle */
			return (0);
		j++;
	}
	return (1);
}

/* read from file map and populate m->grid
getline() */
int	read_grid(FILE *fp, t_map *m)
{
	char	*line;
	size_t	cap;
	ssize_t	len;
	int		i;

	m->grid = malloc((size_t)m->n * sizeof(char *));
	if (!m->grid)
		return (-1);
	m->w = -1;
	i = 0;
	while (i < m->n)
	{
		line = NULL;
		cap = 0;
		len = getline(&line, &cap, fp);
		if (len < 1 || line[len - 1] != '\n')
			return (free(line), free_grid(m->grid, i), -1);
		line[--len] = '\0';
		if (m->w == -1)
			m->w = (int)len;
		if ((int)len != m->w || m->w < 1 || !valid_line(line, m))
			return (free(line), free_grid(m->grid, i), -1);
		m->grid[i++] = line;
	}
	return (0);
}

/*
** dp[i][j] = side of biggest empty square ending at (i, j).
**   obstacle/full -> 0 ; first row/col -> 1 ; else 1 + min(up, left, up-left).
** Flat array, size_t index to avoid int overflow on huge maps.
** Strict '>' on scan => topmost-then-leftmost tie-break for free.
*/
static int	find_lowest(int *dp, t_map *m, int i, int j)
{
	int	v;
	size_t pos = (size_t)i;

	if (m->grid[i][j] != m->e)
		return (0);
	if (i == 0 || j == 0)
		return (1);
	v = dp[(pos - 1) * m->w + j]; // top: find lowest
	if (dp[pos * m->w + j - 1] < v) // left
		v = dp[pos * m->w + j - 1];
	if (dp[(pos - 1) * m->w + j - 1] < v) // top left
		v = dp[(size_t)(i - 1) * m->w + j - 1];
	return (v + 1);
}

static void	fill_square(t_map *m, int bi, int bj, int side)
{
	int	i;
	int	j;

	i = bi - side + 1;
	while (i <= bi)
	{
		j = bj - side + 1;
		while (j <= bj)
			m->grid[i][j++] = m->f;
		i++;
	}
}

static int	run_dp(t_map *m, int *dp, int *bi, int *bj)
{
	int	i;
	int	j;
	int	best;

	best = 0;
	i = 0;
	while (i < m->n)
	{
		j = 0;
		while (j < m->w)
		{
			size_t idx = (size_t)i * m->w + j;
			dp[idx] = find_lowest(dp, m, i, j);
			if (dp[idx] > best)
			{
				best = dp[idx];
				*bi = i;
				*bj = j;
			}
			j++;
		}
		i++;
	}
	return (best);
}

int	solve(t_map *m)
{
	int	*dp;
	int	best;
	int	bi;
	int	bj;

	dp = calloc((size_t)m->n * (size_t)m->w, sizeof(int));
	if (!dp)
		return (-1);
	bi = 0;
	bj = 0;
	best = run_dp(m, dp, &bi, &bj);
	if (best > 0)
		fill_square(m, bi, bj, best);
	free(dp);
	return (0);
}

static void	print_grid(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->n)
	{
		fputs(m->grid[i], stdout);
		fputs("\n", stdout);
		i++;
	}
}

int	process(FILE *fp)
{
	t_map	m;

	if (read_header(fp, &m) == -1)
		return (-1);
	if (read_grid(fp, &m) == -1)
		return (-1);
	if (solve(&m) == -1)
		return (free_grid(m.grid, m.n), -1);
	print_grid(&m);
	free_grid(m.grid, m.n);
	return (0);
}

int main(int argc, char** argv)
{
	FILE *fp;
	int i;

	if (argc == 2)
	{
       if (process(stdin) == -1)
				fprintf(stderr, "map err\n");
		return 0;
	}
	i = 1;
	while (i < argc)
	{
		fp = fopen(argv[i], "r");
		if (!fp)
			fprintf(stderr, "map err\n");
		else
		{
			if (process(fp) == -1)
				fprintf(stderr, "map err\n");
			fclose(fp);
		}
		if (argc > 2)
			fprintf(stdout, "\n");
		i++;
	}
	return 0;
}