/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:22:52 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/18 14:44:26 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_map_height(char	**file, int start_row)
{
	int	i;

	i = start_row;
	while (file[i] && is_map_line(file[i]))
		i++;
	return (i - start_row);
}

int	get_map_width(char **file, int start_row, int height)
{
	int	width;
	int	end_row;
	int	tmp;

	width = 0;
	end_row = start_row + height;
	while (start_row < end_row)
	{
		tmp = ft_strlen(file[start_row]);
		tmp += 1;
		if (tmp > width)
			width = tmp;
		start_row++;
	}
	return (width);
}

int	find_first_map_line(char **file)
{
	int		i;
	char	*line;

	i = 0;
	line = file[0];
	while (!is_map_line(line))
	{
		i++;
		line = file[i];
	}
	return (i);
}

int	is_authorized_char(char c)
{
	int	i;

	i = 0;
	while (AUTHORIZED_MAP_CHARS[i])
	{
		if (AUTHORIZED_MAP_CHARS[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_map_line(const char *line)
{
	int	i;
	int	has_one;

	i = 0;
	has_one = 0;
	while (line[i])
	{
		if (line[i] == '1')
			has_one = 1;
		else if (!is_authorized_char(line[i]))
			return (0);
		i++;
	}
	return (has_one);
}
