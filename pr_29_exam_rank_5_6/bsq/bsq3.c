/*
** gcc -Wall -Wextra -Werror bsq.c && ./a.out
*/

/*
char *line = NULL;
size_t cap = 0;

getline(&line, &cap, fp);   // cap 0   → malloc(120), cap = 120
getline(&line, &cap, fp);   // cap 120 → line fits, no alloc
getline(&line, &cap, fp);   // cap 120 → 300-char line, realloc, cap = 300
cap = 0 + line = NULL is the documented way to say allocate from scratch
*/

#include <stdio.h>
#include <stdlib.h>

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	read_header(FILE *fp, int *n, char *e, char *o, char *f)
{
	char	*junk;
	size_t	cap;

	if (fscanf(fp, "%d %c %c %c", n, e, o, f) != 4)
		return (-1);
	junk = NULL;
	cap = 0;
	if (getline(&junk, &cap, fp) == -1)
	{
		free(junk);
		return (-1);
	}
	free(junk);
	if (*n < 1)
		return (-1);
	if (*e == *o || *e == *f || *o == *f)
		return (-1);
	return (0);
}

int	read_map(FILE *fp, int n, char e, char o, char ***out, int *w)
{
	char	**map;
	char	*line;
	size_t	cap;
	ssize_t	len;
	int		i;
	int		j;

	map = malloc(n * sizeof(char *));
	if (!map)
		return (-1);
	*w = -1;
	i = 0;
	while (i < n)
	{
		line = NULL;
		cap = 0;
		len = getline(&line, &cap, fp); // cap: allocated capacity, line includes the \n, excludes \0;
		if (len < 1 || line[len - 1] != '\n')
			return (free(line), free_map(map, i), -1);
		len--;
		line[len] = '\0'; // \n\0
		if (*w == -1)
			*w = (int)len;
		if ((int)len != *w || *w < 1)
			return (free(line), free_map(map, i), -1);
		j = 0;
		while (j < *w)
		{
			if (line[j] != e && line[j] != o)
				return (free(line), free_map(map, i), -1);
			j++;
		}
		map[i] = line;
		i++;
	}
	*out = map;
	return (0);
}

/*
** dp[i][j] = side of biggest empty square ending at (i, j).
**   obstacle      -> 0
**   first row/col -> 1
**   else          -> 1 + min(up, left, up-left)
** One flat array, index i * w + j. Strict '>' gives topmost-then-leftmost.
*/
int	solve(char **map, int n, int w, char e, char f)
{
	int	*dp;
	int	i;
	int	j;
	int	v;
	int	best;
	int	bi;
	int	bj;

	dp = calloc((size_t)n * w, sizeof(int));
	if (!dp)
		return (-1);
	best = 0;
	bi = 0;
	bj = 0;
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < w)
		{
			if (map[i][j] != e)
				dp[i * w + j] = 0;
			else if (i == 0 || j == 0)
				dp[i * w + j] = 1;
			else
			{
				v = dp[(i - 1) * w + j];
				if (dp[i * w + j - 1] < v)
					v = dp[i * w + j - 1];
				if (dp[(i - 1) * w + j - 1] < v)
					v = dp[(i - 1) * w + j - 1];
				dp[i * w + j] = v + 1;
			}
			if (dp[i * w + j] > best)
			{
				best = dp[i * w + j];
				bi = i;
				bj = j;
			}
			j++;
		}
		i++;
	}
	free(dp);
	i = bi - best + 1;
	while (i <= bi)
	{
		j = bj - best + 1;
		while (j <= bj)
			map[i][j++] = f;
		i++;
	}
	return (0);
}

int	process(FILE *fp)
{
	int		n;
	int		w;
	char	e;
	char	o;
	char	f;
	char	**map;
	int		i;

	if (read_header(fp, &n, &e, &o, &f) == -1)
		return (-1);
	if (read_map(fp, n, e, o, &map, &w) == -1)
		return (-1);
	if (solve(map, n, w, e, f) == -1)
		return (free_map(map, n), -1);
	i = 0;
	while (i < n)
	{
		fputs(map[i], stdout);
		fputs("\n", stdout);
		i++;
	}
	free_map(map, n);
	return (0);
}

int	main(int argc, char **argv)
{
	FILE	*fp;
	int		i;

	if (argc < 2)
	{
		if (process(stdin) == -1)
			fprintf(stderr, "map error\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		fp = fopen(argv[i], "r");
		if (!fp)
			fprintf(stderr, "map error\n");
		else
		{
			if (process(fp) == -1)
				fprintf(stderr, "map error\n");
			fclose(fp);
		}
		if (argc > 2)
			fprintf(stdout, "\n");
		i++;
	}
	return (0);
}