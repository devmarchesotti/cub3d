/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:27:11 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 19:19:52 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	populate_line_map(int len, char *map_line, char *file_line)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (file_line[i] == '\n' || file_line[i] == 0)
		{
			while (i < len - 1)
			{
				map_line[i] = ' ';
				i++;
			}
		}
		else
		{
			map_line[i] = file_line[i];
			i++;
		}
	}
	map_line[i] = 0;
}

int	create_map(t_map *map_struct, char **file, int start_row)
{
	char	**map;
	int		i;	

	map = malloc(sizeof(char *) * (map_struct->height + 1));
	if (!map)
		return (0);
	i = 0;
	while (i < map_struct->height)
	{
		map[i] = malloc(map_struct->width * sizeof(char));
		if (!map[i])
		{
			while (i > 0)
				free(map[i--]);
			free(map);
			return (0);
		}
		populate_line_map(map_struct->width, map[i], file[start_row]);
		start_row++;
		i++;
	}
	map[i] = NULL;
	map_struct->map = map;
	return (1);
}

void	set_player_orientation(t_map *map, char orientation)
{
	if (orientation == 'N')
		map->orientation = M_PI * 3 / 2;
	else if (orientation == 'E')
		map->orientation = 0;
	else if (orientation == 'S')
		map->orientation = M_PI / 2;
	else if (orientation == 'W')
		map->orientation = M_PI;
}

void	find_player_orientation(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width - 1)
		{
			if (ft_strchr("NESW", map->map[y][x]))
			{
				map->start_x = x;
				map->start_y = y;
				set_player_orientation(map, map->map[y][x]);
				map->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	parse_map(t_map *map, char **file)
{
	int	start_row;

	start_row = find_first_map_line(file);
	map->height = get_map_height(file, start_row);
	map->width = get_map_width(file, start_row, map->height);
	if (!create_map(map, file, start_row))
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (1);
	}
	if (!is_map_valid(map))
		return (1);
	find_player_orientation(map);
	return (0);
}
