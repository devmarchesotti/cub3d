/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool-box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:07:13 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 06:40:52 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_exit(t_cube3d *cube3d, char *str, int exit_code)
{
	if (str)
		ft_putstr_fd(str, 2);
	if (cube3d)
		free_all(cube3d);
	exit(exit_code);
}

int	ft_error(char *message)
{
	ft_putstr_fd(message, 2);
	return (1);
}

int	is_empty_or_spaces(const char *line)
{
	while (*line)
	{
		if (!(*line == ' ' || *line == '\n'))
		{
			return (0);
		}
		line++;
	}
	return (1);
}

void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	printf("\n========MAP=========\n");
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				printf("%c", 254);
			else if (map[i][j] == '0')
				printf(" ");
			else
				printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("=======END MAP=======\n");
}

void	printf_all_arg(t_cube3d *cube3d)
{
	print_map(cube3d->map->map);
	printf("HEIGHT = %d\n", cube3d->map->height);
	printf("WIDTH = %d\n", cube3d->map->width);
	printf("Player position is x=%d, y=%d facing %f\n", \
	cube3d->map->start_x, cube3d->map->start_y, cube3d->map->orientation);
	printf("no = %s", cube3d->textures->no);
	printf("so = %s", cube3d->textures->so);
	printf("we = %s", cube3d->textures->we);
	printf("ea = %s", cube3d->textures->ea);
	printf("c = %d,%d,%d\n", cube3d->ceiling->red, \
	cube3d->ceiling->green, cube3d->ceiling->blue);
	printf("f = %d,%d,%d\n", cube3d->floor->red, \
	cube3d->floor->green, cube3d->floor->blue);
	printf("Player position is x=%.1f, y=%.1f facing %f\n", \
	cube3d->player->x, cube3d->player->y, cube3d->player->direction);
}
