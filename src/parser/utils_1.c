/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:21:58 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 06:41:41 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	preliminary_checks(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (0);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nFile extension must be .cub\n", 2);
		return (0);
	}
	return (1);
}

int	init_textures(t_cube3d *cube3d)
{
	cube3d->textures = malloc(sizeof(t_textures));
	if (!cube3d->textures)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (1);
	}
	cube3d->textures->no = NULL;
	cube3d->textures->so = NULL;
	cube3d->textures->we = NULL;
	cube3d->textures->ea = NULL;
	cube3d->textures->no_texture = NULL;
	cube3d->textures->so_texture = NULL;
	cube3d->textures->we_texture = NULL;
	cube3d->textures->ea_texture = NULL;
	return (0);
}

int	init_colors(t_cube3d *cube3d)
{
	cube3d->ceiling = malloc(sizeof(t_colors));
	if (!cube3d->ceiling)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		cube3d->floor = NULL;
		return (1);
	}
	cube3d->floor = malloc(sizeof(t_colors));
	if (!cube3d->floor)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (1);
	}
	return (0);
}

int	init_cub3d(t_cube3d *cube3d)
{
	cube3d->textures = NULL;
	cube3d->ceiling = NULL;
	cube3d->floor = NULL;
	cube3d->map = NULL;
	cube3d->player = NULL;
	if (init_textures(cube3d))
		return (1);
	if (init_colors(cube3d))
		return (1);
	cube3d->map = malloc(sizeof(t_map));
	if (!cube3d->map)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (1);
	}
	cube3d->map->map = NULL;
	return (0);
}
