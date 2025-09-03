/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dom.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:29:36 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 19:21:11 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->map)
	{
		free_split(map->map);
		map->map = NULL;
	}
	free(map);
	map = NULL;
}

void	free_window(t_window *window)
{
	if (!window)
		return ;
	free(window->title);
	window->title = NULL;
	free(window);
	window = NULL;
}

void	free_player(t_player *player)
{
	if (!player)
		return ;
	free(player);
	player = NULL;
}

void	free_all(t_cube3d *cube3d)
{
	if (!cube3d)
		return ;
	if (cube3d->window)
		free_window(cube3d->window);
	if (cube3d->textures)
		free_textures(cube3d->textures);
	if (cube3d->floor)
		free_colors(cube3d->floor);
	if (cube3d->ceiling)
		free_colors(cube3d->ceiling);
	if (cube3d->map)
		free_map(cube3d->map);
	if (cube3d->player)
		free_player(cube3d->player);
	if (cube3d->mousse)
		free(cube3d->mousse);
	free(cube3d);
	cube3d = NULL;
}
