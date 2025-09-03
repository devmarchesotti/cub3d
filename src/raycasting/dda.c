/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:13:30 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 20:55:47 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	initialize_dda_algorithm(t_player *player, float ray_direction, \
		t_dda *dda)
{
	dda->map_pos_x = (int)floorf(player->x);
	dda->map_pos_y = (int)floorf(player->y);
	dda->ray_dir_x = cosf(ray_direction);
	dda->ray_dir_y = sinf(ray_direction);
	dda->delta_dist_x = fabsf(1.0f / dda->ray_dir_x);
	dda->delta_dist_y = fabsf(1.0f / dda->ray_dir_y);
	if (dda->ray_dir_x < 0)
		dda->step_x = -1;
	else
		dda->step_x = 1;
	if (dda->ray_dir_y < 0)
		dda->step_y = -1;
	else
		dda->step_y = 1;
	if (dda->step_x < 0)
		dda->side_dist_x = (player->x - dda->map_pos_x) * dda->delta_dist_x;
	else
		dda->side_dist_x = (dda->map_pos_x + 1.0f - player->x) \
		* dda->delta_dist_x;
	if (dda->step_y < 0)
		dda->side_dist_y = (player->y - dda->map_pos_y) * dda->delta_dist_y;
	else
		dda->side_dist_y = (dda->map_pos_y + 1.0f - player->y) \
		* dda->delta_dist_y;
}

void	perform_dda(t_cube3d *cube, t_dda *d)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (d->side_dist_x < d->side_dist_y)
		{
			d->side_dist_x += d->delta_dist_x;
			d->map_pos_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_dist_y += d->delta_dist_y;
			d->map_pos_y += d->step_y;
			d->side = 1;
		}
		if (d->map_pos_x < 0 || d->map_pos_x >= cube->map->width \
		|| d->map_pos_y < 0 || d->map_pos_y >= cube->map->height \
		|| cube->map->map[d->map_pos_y][d->map_pos_x] == '1')
			hit = 1;
	}
}
