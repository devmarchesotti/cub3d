/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:28:28 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 08:13:58 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	has_single_starting_position(char **map_data)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (map_data[i])
	{
		j = 0;
		while (map_data[i][j])
		{
			if (map_data[i][j] == 'N' || map_data[i][j] == 'S' ||
				map_data[i][j] == 'E' || map_data[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count == 1);
}

int	flood_fill(t_map *info, int x, int y)
{
	int	up;
	int	down;
	int	left;
	int	right;

	if (x < 0 || y < 0 || x >= info->height || y >= info->width)
		return (0);
	if (info->map[x][y] == '1' || info->map[x][y] == 'v')
		return (1);
	info->map[x][y] = 'v';
	up = flood_fill(info, x - 1, y);
	down = flood_fill(info, x + 1, y);
	left = flood_fill(info, x, y - 1);
	right = flood_fill(info, x, y + 1);
	return (up && down && left && right);
}

char	**get_map_dup(char **og, int height)
{
	int		i;
	char	**dup;

	i = 0;
	dup = malloc(sizeof(char *) * (height + 1));
	if (!dup)
		return (NULL);
	while (og[i])
	{
		dup[i] = ft_strdup(og[i]);
		if (!dup[i])
		{
			while (i > 0)
				free(dup[--i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	find_starting_position(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' ||
				map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->start_x = i;
				map->start_y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	is_map_valid(t_map *map)
{
	t_map	*dup_map;

	if (!has_single_starting_position(map->map))
		return (ft_putstr_fd \
		("Error\nMultiplayer or ghost mode yet not implemented\n", 2), 0);
	dup_map = malloc(sizeof(t_map));
	if (!dup_map)
		return (ft_putstr_fd("Error\nMalloc Failled\n", 2), 0);
	dup_map->map = get_map_dup(map->map, map->height);
	if (!dup_map->map)
		return (ft_putstr_fd("Error\nMalloc Failed\n", 2), 0);
	dup_map->height = map->height;
	dup_map->width = map->width;
	find_starting_position(map);
	dup_map->map[map->start_x][map->start_y] = '0';
	if (!flood_fill(dup_map, map->start_x, map->start_y))
	{
		free_map(dup_map);
		return (ft_putstr_fd("Error\nMap is not closed\n", 2), 0);
	}
	free_map(dup_map);
	return (1);
}
