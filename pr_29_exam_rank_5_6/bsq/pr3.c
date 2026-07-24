#include <stdio.h>
#include <stdlib.h>

void free_map(char **map, int rows)
{
	int i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
/* fscanf to update num, empty, obstacle, fill, getline to rmv junk after that, check valid values */
int read_header(FILE* fp, int *num, char *empty, char *obstacle, char *fill)
{
	char *junk;
	size_t cap;

	if (fscanf(fp, "%d %c % c%c", num, empty, obstacle, fill) != 4)
		return -1;
	junk = NULL;
	cap = 0;
	if (getline(&junk, &cap, fp) == -1)
	{
		free(junk);
		return -1;
	}
	free(junk);
	if (*num < 1) return -1;
	if (*empty== *obstacle || *empty == *fill || *obstacle == *fill)
		return -1;
	return 0;
}

int read_map(FILE *fp, int num, char empty, char obstacle, char ***out, int *w)
{
	char	**map;
	char	*line;
	size_t	cap;
	ssize_t len;
	int i, j;

	map = malloc(num * sizeof (char*));
	if (!map) return -1;
	*w = -1, i = 0;
	while (i < num)
	{
		line = NULL;
		cap = 0;
		len = getline(&line, &cap, fp);
		if (len < 1 || line[len - 1] != '\n')
			return (free(line), free_map(map, i), -1);
		len--;
		line[len] = '\0'; // /n/0
		if (*w == -1)
			*w = (int)len;
		if ((int)len != *w || *w < 1)
			return (free(line), free_map(map, i), -1);
		j = 0;
		while (j < *w)
		{
			if (line[j] != empty && line[j] != obstacle)
				return (free(line), free_map(map, i), -1);
			j++;
		}
		map[i] = line;
		i++;
	}
	*out = map;
	return 0;
}

int min()
{
	
}

int solve(char **map, int n, int w, char e, char f)
{
	int *dp;
	int i = 0, j = 0, val, best = 0, bi = 0, bj = 0;

	dp = calloc((size_t)n * w, sizeof(int));
	if (!dp) return -1;
	while (i < n)
	{
		j = 0;
		while (j < w)
		{
			if (map[i][j])
		}
		i++;
	}
}

int process(FILE *fp)
{
	int		num, width, i;
	char 	empty, obstacle, fill;
	char 	**map;

	if (read_header(fp, &num, &empty, &obstacle, &fill) == -1)	
		return -1;
	if (read_map(fp, num, empty, obstacle, &map, &width) == -1)
		return -1;
	if (solve(map, num, width, empty, fill) == -1)
		return -1;
	i = 0;
	while (i < num)
	{	
		fputs(map[i], stdout);
		fputs("\n", stdout);
		i++;
	}
	free_map(map, num);
	return 0;
}

int main(int argc, char **argv)
{
	FILE *fp;
	int i;

	if (argc < 2)
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