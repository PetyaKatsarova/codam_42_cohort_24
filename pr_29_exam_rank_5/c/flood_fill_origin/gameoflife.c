#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define READ_CHUNK 4096

typedef struct s_grid
{
	int		width;
	int		height;
	char	*cells;
}	t_grid;

static void	grid_free(t_grid *grid)
{
	if (grid->cells != NULL)
		free(grid->cells);
	grid->cells = NULL;
	grid->width = 0;
	grid->height = 0;
}

static char	*read_all(int fd, int *raw_size)
{
	char	buffer[READ_CHUNK];
	char	*raw;
	char	*tmp;
	int		used;
	ssize_t	nread;

	raw = NULL;
	used = 0;
	while (1)
	{
		nread = read(fd, buffer, READ_CHUNK);
		if (nread < 0)
		{
			free(raw);
			return (NULL);
		}
		if (nread == 0)
			break ;
		tmp = (char *)realloc(raw, used + (int)nread + 1);
		if (tmp == NULL)
		{
			free(raw);
			return (NULL);
		}
		raw = tmp;
		memcpy(raw + used, buffer, (size_t)nread);
		used += (int)nread;
	}
	if (raw == NULL)
		return (NULL);
	raw[used] = '\0';
	*raw_size = used;
	return (raw);
}

static int	parse_map(const char *raw, int raw_size, t_grid *grid)
{
	int	width;
	int	height;
	int	row_len;
	int	i;
	int	index;

	if (raw_size <= 0)
		return (0);
	width = 0;
	while (width < raw_size && raw[width] != '\n')
	{
		if (raw[width] != 'X' && raw[width] != '.')
			return (0);
		width++;
	}
	if (width == 0)
		return (0);
	height = 0;
	row_len = 0;
	i = 0;
	while (i < raw_size)
	{
		if (raw[i] == '\n')
		{
			if (row_len != width)
				return (0);
			height++;
			row_len = 0;
		}
		else if (raw[i] == 'X' || raw[i] == '.')
			row_len++;
		else
			return (0);
		i++;
	}
	if (row_len != 0)
	{
		if (row_len != width)
			return (0);
		height++;
	}
	if (height == 0)
		return (0);
	grid->width = width;
	grid->height = height;
	grid->cells = (char *)malloc((size_t)(width * height));
	if (grid->cells == NULL)
		return (0);
	index = 0;
	i = 0;
	while (i < raw_size)
	{
		if (raw[i] != '\n')
		{
			grid->cells[index] = raw[i];
			index++;
		}
		i++;
	}
	return (1);
}

static int	alive_neighbors(const t_grid *grid, int row, int col)
{
	static int	dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	static int	dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int		count;
	int		k;
	int		nr;
	int		nc;

	count = 0;
	k = 0;
	while (k < 8)
	{
		nr = row + dr[k];
		nc = col + dc[k];
		if (nr >= 0 && nr < grid->height && nc >= 0 && nc < grid->width)
		{
			if (grid->cells[nr * grid->width + nc] == 'X')
				count++;
		}
		k++;
	}
	return (count);
}

static void	game_of_life_step(const t_grid *grid, char *next)
{
	int	row;
	int	col;
	int	idx;
	int	alive;

	row = 0;
	while (row < grid->height)
	{
		col = 0;
		while (col < grid->width)
		{
			idx = row * grid->width + col;
			alive = alive_neighbors(grid, row, col);
			if (grid->cells[idx] == 'X')
			{
				if (alive == 2 || alive == 3)
					next[idx] = 'X';
				else
					next[idx] = '.';
			}
			else if (alive == 3)
				next[idx] = 'X';
			else
				next[idx] = '.';
			col++;
		}
		row++;
	}
}

static void	print_grid(const char *cells, int width, int height)
{
	int	row;
	int	col;
	int	idx;

	row = 0;
	while (row < height)
	{
		col = 0;
		while (col < width)
		{
			idx = row * width + col;
			write(1, &cells[idx], 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

int	main(int argc, char **argv)
{
	t_grid	grid;
	char	*raw;
	char	*next;
	int		raw_size;
	int		cells;
	int		fd;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write(1, "\n", 1), 1);
	raw = read_all(fd, &raw_size);
	close(fd);
	if (raw == NULL)
		return (write(1, "\n", 1), 1);
	grid.cells = NULL;
	if (!parse_map(raw, raw_size, &grid))
	{
		free(raw);
		return (write(1, "\n", 1), 1);
	}
	free(raw);
	cells = grid.width * grid.height;
	next = (char *)malloc((size_t)cells);
	if (next == NULL)
	{
		grid_free(&grid);
		return (write(1, "\n", 1), 1);
	}
	game_of_life_step(&grid, next);
	print_grid(next, grid.width, grid.height);
	free(next);
	grid_free(&grid);
	return (0);
}
