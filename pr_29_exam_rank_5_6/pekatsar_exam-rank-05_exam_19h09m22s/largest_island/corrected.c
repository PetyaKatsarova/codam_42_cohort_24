#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * int arr[10];                             // 10 ints on the stack
 * int *stack = malloc(10 * sizeof(int));   // 10 ints on the heap
 * =============================================
 * **buf:
 * holds       chars: X . V \n
 * slot size   1 byte
 * stays full  yes
 *
 * **stack:
 * holds       numbers: positions in buf
 * slot size   4 bytes
 * stays full  no - grows and shrinks
 *
 * buf[5]   = 'X'
 * stack[0] = 5
 * =============================================
 * Why:
 * we take a position. Now we must look at its 4 neighbours. we take one of
 * those. Now it has 4 neighbours. The other 3 are still waiting.
 *
 * Somewhere we have to write down the ones still waiting.
 *
 * That's the stack. A note pad of positions we took but haven't looked
 * around from yet.
 *
 * It's usually nearly empty - only holds the current frontier. Sized
 * width * height only because in the worst case everything is waiting.
 *
 * NB!! each line, including last, ends in newline ('\n')
 */

int	width_len(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	return (i);
}

int	validate_map(char *buf, int *width, int *height)
{
	int	i = 0, len = 0, h = 0;
	int	w = width_len(buf);

	if (w == 0)
		return (-1);
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			if (w != len)
				return (-1);
			len = 0;
			h++;
		}
		else if (buf[i] != 'X' && buf[i] != '.')
			return (-1);
		else
			len++;
		i++;
	}
	if (len > 0)
		return (-1);
	if (h == 0)
		return (-1);
	*width = w;
	*height = h;
	return (0);
}

/*
Claims one position: if it is inside the buffer and holds 'X', mark it 'V'
and record it on the stack for later neighbour checking. Marking at push
time (not pop time) guarantees each position is stacked exactly once.
top is the count of positions waiting.
*/
static void	push(char *buf, int *stack, int *top, int idx, int map_len)
{
	if (idx < 0 || idx >= map_len || buf[idx] != 'X')
		return ;
	buf[idx] = 'V';
	stack[(*top)++] = idx;
}

int	flood_fill(char *buf, int *stack, int i, int w, int map_len)
{
	int	size = 0, top = 0, idx;

	push(buf, stack, &top, i, map_len);
	while (top > 0)
	{
		idx = stack[--top];
		size++;
		push(buf, stack, &top, idx + 1, map_len);
		push(buf, stack, &top, idx - 1, map_len);
		push(buf, stack, &top, idx + w + 1, map_len);
		push(buf, stack, &top, idx - w - 1, map_len);
	}
	return (size);
}

int	largest_island(char *buf, int *stack, int w, int map_len)
{
	int	i = 0, size = 0, largest = 0;

	while (i < map_len)
	{
		if (buf[i] == 'X')
		{
			size = flood_fill(buf, stack, i, w, map_len);
			if (size > largest)
				largest = size;
		}
		i++;
	}
	return (largest);
}

void	putnbr(int num)
{
	char	c;

	if (num > 9)
		putnbr(num / 10);
	c = num % 10 + '0';
	write(1, &c, 1);
}

void	print_msg(void)
{
	char	*msg;
	int		i;

	msg = "Map Error";
	i = 0;
	while (msg[i])
	{
		write(1, &msg[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

char	*read_file(char *path, int *map_len)
{
	int			fd;
	char		*buf;
	struct stat	st;

	fd = open(path, O_RDONLY);
	if (fd < 0)	return (NULL);
	if (fstat(fd, &st) < 0)	return (close(fd), NULL);
	buf = malloc(st.st_size + 1);
	if (!buf) return (close(fd), NULL);
	*map_len = read(fd, buf, st.st_size);
	close(fd);
	if (*map_len <= 0)	return (free(buf), NULL);
	buf[*map_len] = '\0';
	return (buf);
}

int	main(int argc, char **argv)
{
	int		map_len, width, height;
	int		*stack;
	char	*buf;

	if (argc != 2)
		return (print_msg(), 1);
	buf = read_file(argv[1], &map_len);
	if (!buf)
		return (print_msg(), 1);
	if (validate_map(buf, &width, &height) == -1)
		return (free(buf), print_msg(), 1);
	stack = malloc(sizeof(int) * width * height);
	if (!stack)
		return (free(buf), print_msg(), 1);
	putnbr(largest_island(buf, stack, width, map_len));
	write(1, "\n", 1);
	return (free(stack), free(buf), 0);
}