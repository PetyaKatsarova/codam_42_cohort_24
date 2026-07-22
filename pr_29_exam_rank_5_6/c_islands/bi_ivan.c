#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF 2000

int	width_len(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	return (i);
}

int	valid_map(char *buf)
{
	int	w;
	int	other_w;
	int	i;

	w = width_len(buf);
	other_w = 0;
	i = 0;
	if (w == 0)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			if (other_w != w)
				return (0);
			other_w = 0;
		}
		else if (buf[i] != 'X' && buf[i] != '.')
			return (0);
		else
			other_w++;
		i++;
	}
	if (other_w != 0 && other_w != w)
		return (0);
	return (1);
}

int	floodfill(char *buf, int i, int w, int bytes)
{
	int	size;

	size = 0;
	if (i < 0 || i >= bytes || buf[i] != 'X')
		return (0);
	buf[i] = 'V';
	size = 1;
	if (i + 1 < bytes && buf[i + 1] != '\n')
		size += floodfill(buf, i + 1, w, bytes);
	if (i > 0 && buf[i - 1] != '\n')
		size += floodfill(buf, i - 1, w, bytes);
	size += floodfill(buf, i + w + 1, w, bytes);
	size += floodfill(buf, i - w - 1, w, bytes);
	return (size);
}

int	largest_island(char *buf, int bytes)
{
	int	w;
	int	i;
	int	largest;
	int	size;

	w = width_len(buf);
	i = 0;
	largest = 0;
	while (buf[i])
	{
		if (buf[i] == 'X')
		{
			size = floodfill(buf, i, w, bytes);
			if (size > largest)
				largest = size;
		}
		i++;
	}
	return (largest);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n > 9)
		ft_putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

int	main(int arc, char *argv[])
{
	int		fd;
	int		bytes;
	char	*buf;
	int		largest;

	if (arc != 2)
		return (write(1, "\n", 1), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write(1, "\n", 1), 1);
	buf = malloc(BUF);
	if (!buf)
		return (close(fd), write(1, "\n", 1), 1);
	bytes = read(fd, buf, BUF - 1);
	if (bytes < 1)
		return (close(fd), free(buf), write(1, "\n", 1), 1);
	close(fd);
	buf[bytes] = '\0';
	if (!valid_map(buf))
		return (free(buf), write(1, "\n", 1), 1);
	largest = largest_island(buf, bytes);
	ft_putnbr(largest);
	write(1, "\n", 1);
	free(buf);
	return (0);
}