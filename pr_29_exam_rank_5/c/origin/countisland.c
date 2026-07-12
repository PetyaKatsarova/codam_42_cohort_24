/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   countisland.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/05 21:48:07 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/07/12 15:58:16 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
	int	i;
	int	len;
	int	w;

	w = width_len(buf);
	i = 0;
	len = 0;
	if (w == 0)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			if (len != w)
				return (0);
			len = 0;
		}
		else if (buf[i] != 'X' && buf[i] != '.')
			return (0);
		else
			len++;
		i++;
	}
	if (len != 0)
		return (len != 0 && len != w);
	return (1);
}

void	floodfill(char *buf, int i, int w, char island, int bytes)
{
	if (i < 0 || i >= bytes || buf[i] != 'X')
		return ;
	buf[i] = island;
	if (i + 1 < bytes && buf[i + 1] != '\n')
		floodfill(buf, i + 1, w, island, bytes);
	if (i - 1 >= 0 && buf[i - 1] != '\n')
		floodfill(buf, i - 1, w, island, bytes);
	if (i + w + 1 < bytes)
		floodfill(buf, i + w + 1, w, island, bytes);
	if (i - w - 1 >= 0)
		floodfill(buf, i - w - 1, w, island, bytes);
}

int	count_island(char *buf, int bytes)
{
	int		i;
	int		w;
	char	island;

	i = 0;
	w = width_len(buf);
	island = '0';
	while (buf[i])
	{
		if (buf[i] == 'X')
		{
			floodfill(buf, i, w, island, bytes);
			island++;
		}
		i++;
	}
	return (island - '0');
}

int	main(int arc, char *argv[])
{
	int		fd;
	char	*buf;
	int		bytes;

	if (arc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write(1, "\n", 1), 1);
	buf = malloc(BUF);
	if (!buf)
		return (close(fd), write(1, "\n", 1), 1);
	bytes = read(fd, buf, BUF - 1);
	if (bytes < 1)
		return (free(buf), close(fd), write(1, "\n", 1), 1);
	close(fd);
	buf[bytes] = '\0';
	if (!valid_map(buf))
		return (free(buf), write(1, "\n", 1), 1);
	count_island(buf, bytes);
	write(1, buf, bytes);
	write(1, "\n", 1);
	free(buf);
	return (0);
}