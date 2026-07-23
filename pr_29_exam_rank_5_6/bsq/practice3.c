#include <stdio.h>
#include <stdlib.h>
/*
The FILE structure is an opaque type that holds information about the file (file descriptor, buffer, position, etc.).Can use the ptr with standard I/O functions like fopen(), fclose(), fread(), fwrite(), fgets(), fputs(), fprintf()

char *line = NULL;
size_t cap = 0;

getline(&line, &cap, fp);   // cap 0   → malloc(120), cap = 120
getline(&line, &cap, fp);   // cap 120 → line fits, no alloc
getline(&line, &cap, fp);   // cap 120 → 300-char line, realloc, cap = 300
cap = 0 + line = NULL is the documented way to say allocate from scratch
*/

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

int read_header(FILE *fp, int *num, char *empty, char *obstacle, char *fill)
{
	char 	*junk;
	size_t	cap;

	if (fscanf(fp, "%d %c %c %c", num, empty, obstacle, fill) != 4)
		return (-1);
	junk = NULL;
	cap = 0;
	if (getline(&junk, &cap, fp) == -1)
		return (free(junk), -1);
	free(junk);
	if (*num < 1) return -1;
	if (*empty == *obstacle || *empty == *fill || *obstacle == *fill) return (-1);
	return 0;
}

int read_map(FILE *fp, int rows, char empty, char obstacle, char ***out, int *w)
{
	char **map, *line;
	size_t cap;
	ssize_t len;
	int i, j;

	map = malloc(rows * sizeof(char *));
	if (!map) return -1;
	*w = -1;
	i = 0;
	while (i < rows)
	{
		line = NULL;
		cap = 0;
		len = getline(&line, &cap, fp);
		if (len < 1 || line[len - 1] != '\n')
			return (free(line), free_map(map, i), -1);
		len--;
		line[len] = '\n'; // \n\0
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
		map[i] = line; // add a row in the map
		i++;
	}
	*out = map; //Publish to caller only on full success. On any failure *out is untouched — no dangling pointer handed back
	return 0;
}

int get_lowest(int *dp, int i, int w, int j)
{
	int lowest = dp[(i - 1) * w + j]; // top
				if (dp[i * w + j - 1] < lowest) // left
					lowest = dp[i * w + j - 1];
				if (dp[(i - 1) * w + j - 1] < lowest) // top left
					lowest = dp[(i - 1) * w + j - 1];
	return lowest;
}

/*
dp(dynamic programming) dp[i][j] = size of biggest empty square ending at(i, j);
obstacle -> 0
first row/col -> 1
else -> 1 + min(left, up-left, left)
*/
int solve(char **map, int rows, int w, char e, char f)
{
	int *dp;
	int i = 0, j, lowest, best = 0, bi = 0, bj = 0;

	dp = calloc((size_t)rows * w, sizeof(int));
	if (!dp) return (-1);
	while (i < rows)
	{
		j = 0;
		while (j < w)
		{
			if (map[i][j] != e) // because we dont have param obstacle; so if we get obstclte we mark with 0
				dp[i * w + j] = 0;
			else if (i == 0 || j == 0)
				dp[i * w + j] = 1;
			else
			{
				lowest = get_lowest(dp, i, w, j);
				dp[i * w + j] = lowest + 1;
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
	i = bi - best + 1; // best row = rowi - num best + 1? dont get it: best num cant never be > rows num:
	while ( i <= bi)
	{
		j = bj - best + 1;
		while (j <= bj)
			map[i][j++] = f;
		i++;
	}
	return 0;
}

int process(FILE *fp)
{
	int rows, width, i;
	char empty, obstacle, fill;
	char **map;

	if (read_header(fp, &rows, &empty, &obstacle, &fill) == -1)
		return (-1);
	if (read_map(fp, rows, empty, obstacle, &map, &width) == -1)
		return (-1);
	if (solve(map, rows, width, empty, fill) == -1)
		return (free_map(map, rows), -1);
	i = 0;
	while (i < rows)
	{
		fputs(map[i], stdout);
		fputs("\n", stdout);
		i++;
	}
	return 0;
}

int main(int argc, char** argv)
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
	fprintf(stderr, "%s\n", argv[1]);
	return 0;
}