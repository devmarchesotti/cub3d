/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:48:51 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 21:12:49 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*read_buffer(int fd, char *remaining)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!remaining)
			remaining = ft_strdup("");
		temp = remaining;
		remaining = ft_strjoin(remaining, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (NULL);
	return (remaining);
}

static char	*extract_line(char **remaining)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	if (!*remaining || !**remaining)
		return (NULL);
	newline_pos = ft_strchr(*remaining, '\n');
	if (newline_pos)
	{
		line = ft_strndup(*remaining, newline_pos - *remaining + 1);
		temp = ft_strdup(newline_pos + 1);
		free(*remaining);
		*remaining = temp;
	}
	else
	{
		line = ft_strdup(*remaining);
		free(*remaining);
		*remaining = NULL;
	}
	return (line);
}

/* char	*get_next_line(int fd)
{
	static char	*remaining;
	static int	last_fd = -1;
	static int	eof_reached = 0;

	if (fd < 0 || BUFFER_SIZE <= 0 || eof_reached)
		return (NULL);
	if (fd != last_fd)
	{
		free(remaining);
		remaining = NULL;
		last_fd = fd;
	}
	remaining = read_buffer(fd, remaining);
	if (!remaining)
	{
		eof_reached = 1;
		return (NULL);
	}
	return (extract_line(&remaining));
} */

char	*get_next_line(int fd)
{
	static char	*remaining;
	static int	last_fd = -1;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fd != last_fd)
	{
		free(remaining);
		remaining = NULL;
		last_fd = fd;
	}
	remaining = read_buffer(fd, remaining);
	if (!remaining)
		return (NULL);
	return (extract_line(&remaining));
}
