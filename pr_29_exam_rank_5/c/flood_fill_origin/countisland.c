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

static void	put_nbr(int n)
{
	char	c;

	if (n >= 10)
		put_nbr(n / 10);
	c = (char)('0' + (n % 10));
	write(1, &c, 1);
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

static int	flood_size(const t_grid *grid, char *seen, int start, int *stack)
{
	int	top;
	int	size;
	int	idx;
	int	row;
	int	col;
	int	next;
	int	width;
	int	height;

	width = grid->width;
	height = grid->height;
	top = 0;
	size = 0;
	stack[top] = start;
	top++;
	seen[start] = 1;
	while (top > 0)
	{
		top--;
		idx = stack[top];
		size++;
		row = idx / width;
		col = idx % width;
		if (row > 0)
		{
			next = idx - width;
			if (seen[next] == 0 && grid->cells[next] == 'X')
			{
				seen[next] = 1;
				stack[top] = next;
				top++;
			}
		}
		if (row + 1 < height)
		{
			next = idx + width;
			if (seen[next] == 0 && grid->cells[next] == 'X')
			{
				seen[next] = 1;
				stack[top] = next;
				top++;
			}
		}
		if (col > 0)
		{
			next = idx - 1;
			if (seen[next] == 0 && grid->cells[next] == 'X')
			{
				seen[next] = 1;
				stack[top] = next;
				top++;
			}
		}
		if (col + 1 < width)
		{
			next = idx + 1;
			if (seen[next] == 0 && grid->cells[next] == 'X')
			{
				seen[next] = 1;
				stack[top] = next;
				top++;
			}
		}
	}
	return (size);
}

static int	count_islands(const t_grid *grid, char *seen, int *stack)
{
	int	idx;
	int	total;
	int	count;

	total = grid->width * grid->height;
	count = 0;
	idx = 0;
	while (idx < total)
	{
		if (seen[idx] == 0 && grid->cells[idx] == 'X')
		{
			flood_size(grid, seen, idx, stack);
			count++;
		}
		idx++;
	}
	return (count);
}

int	main(int argc, char **argv)
{
	t_grid	grid;
	char	*raw;
	char	*seen;
	int		*stack;
	int		raw_size;
	int		result;
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
	seen = (char *)malloc((size_t)cells);
	stack = (int *)malloc((size_t)(cells * sizeof(int)));
	if (seen == NULL || stack == NULL)
	{
		free(seen);
		free(stack);
		grid_free(&grid);
		return (write(1, "\n", 1), 1);
	}
	memset(seen, 0, (size_t)cells);
	result = count_islands(&grid, seen, stack);
	put_nbr(result);
	write(1, "\n", 1);
	free(seen);
	free(stack);
	grid_free(&grid);
	return (0);
}
