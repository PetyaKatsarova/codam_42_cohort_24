/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 16:47:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/19 12:12:45 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_ptr(char **ptr);
char	*join_line(int start, char **buffer_holder);
char	*read_line(int fd, char **buff, char *read_return);
char	*ft_strndup(const char *str, size_t n);

char	*get_next_line(int fd)
{
	static char	*buffer_holder[OPEN_MAX + 1];
	char		*current_buffer;
	char		*res;

	res = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	current_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (current_buffer == NULL)
	{
		free(buffer_holder[fd]);
		buffer_holder[fd] = NULL;
		return (NULL);
	}
	if (!buffer_holder[fd])
		buffer_holder[fd] = ft_strndup("", 1);
	if (buffer_holder[fd])
		res = read_line(fd, &buffer_holder[fd], current_buffer);
	free_ptr(&current_buffer);
	return (res);
}

void	free_ptr(char **ptr)
{
	if (*ptr != NULL && ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*join_line(int start, char **buffer_holder)
{
	char	*result;
	char	*temp;

	if (start <= 0)
	{
		if (**buffer_holder == '\0')
		{
			free_ptr((char **)buffer_holder);
			return (NULL);
		}
		result = ft_strndup(*buffer_holder, ft_strlen(*buffer_holder));
		free(*buffer_holder);
		*buffer_holder = NULL;
		return (result);
	}
	temp = ft_substr(*buffer_holder, start, ft_strlen(*buffer_holder) - start);
	result = ft_strndup(*buffer_holder, start);
	free(*buffer_holder);
	if (!result)
	{
		free(temp);
		temp = NULL;
	}
	*buffer_holder = temp;
	return (result);
}

char	*read_line(int fd, char **buffer_holder, char *current_buff)
{
	ssize_t	bytes_read;
	char	*temp;
	char	*nl;

	nl = ft_strchr(*buffer_holder, '\n');
	while (nl == NULL)
	{
		bytes_read = read(fd, current_buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free_ptr(buffer_holder);
			return (NULL);
		}
		else if (bytes_read <= 0 && buffer_holder)
			return (join_line(bytes_read, buffer_holder));
		current_buff[bytes_read] = 0;
		temp = ft_strjoin(*buffer_holder, current_buff);
		free_ptr(buffer_holder);
		if (!temp)
			return (NULL);
		*buffer_holder = temp;
		if (*buffer_holder)
			nl = ft_strchr(*buffer_holder, '\n');
	}
	return (join_line(nl - *buffer_holder + 1, buffer_holder));
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = (char *)malloc((n + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, str, n + 1);
	return (ptr);
}
