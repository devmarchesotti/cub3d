/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:31:53 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/14 20:43:31 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	open_file(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nFailed to open file");
		return (-1);
	}
	return (fd);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
	{
		perror("Error\nFailed to close file");
		return (-1);
	}
	return (0);
}

int	get_number_of_lines(char *file_name)
{
	int		fd;
	char	*line;
	int		i;

	fd = open_file(file_name);
	if (fd == -1)
		return (-1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close_file(fd);
	return (i);
}

void	get_all_lines(char **file, char *file_name)
{
	int	fd;
	int	i;

	fd = open_file(file_name);
	if (fd == -1)
	{
		free_split(file);
		return ;
	}
	i = 0;
	file[0] = get_next_line(fd);
	while (file[i])
	{
		i++;
		file[i] = get_next_line(fd);
	}
	file[i] = NULL;
}

char	**read_file_lines(char *file_name)
{
	int		nb_line;
	char	**file;

	nb_line = get_number_of_lines(file_name);
	if (nb_line == -1)
		return (NULL);
	file = malloc(sizeof(char *) * (nb_line + 1));
	if (!file)
	{
		ft_putstr_fd("Error\nFailed to allocate memory\n", 2);
		return (NULL);
	}
	get_all_lines(file, file_name);
	return (file);
}
