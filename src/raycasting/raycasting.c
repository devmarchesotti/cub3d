/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:04:39 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 21:17:20 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_slice	compute_slice(int height_screen, float perpDist)
{
	t_slice	s;

	s.line_height = (int)(height_screen / perpDist);
	s.draw_start = -s.line_height / 2 + height_screen / 2;
	s.draw_end = s.line_height / 2 + height_screen / 2;
	if (s.draw_start < 0)
	{
		s.draw_start = 0;
	}
	if (s.draw_end >= height_screen)
	{
		s.draw_end = height_screen - 1;
	}
	return (s);
}

t_texinfo	select_texture_info(t_cube3d *cube, t_player *player, t_dda *dda, \
								float perp_distance)
{
	t_texinfo	texture;

	if (dda->side == 0)
		texture.inter_wall_x = player->y + perp_distance * dda->ray_dir_y;
	else
		texture.inter_wall_x = player->x + perp_distance * dda->ray_dir_x;
	texture.inter_wall_x -= floorf(texture.inter_wall_x);
	if (dda->side == 0 && dda->step_x > 0)
		texture.tex = cube->textures->ea_texture;
	else if (dda->side == 0 && dda->step_x < 0)
		texture.tex = cube->textures->we_texture;
	else if (dda->side == 1 && dda->step_y > 0)
		texture.tex = cube->textures->so_texture;
	else
		texture.tex = cube->textures->no_texture;
	texture.x_cord_text = (int)(texture.inter_wall_x * texture.tex->width);
	if ((dda->side == 0 && dda->step_x < 0) || \
		(dda->side == 1 && dda->step_y > 0))
		texture.x_cord_text = texture.tex->width - texture.x_cord_text - 1;
	if (texture.x_cord_text < 0)
		texture.x_cord_text = 0;
	if (texture.x_cord_text >= (int)texture.tex->width)
		texture.x_cord_text = texture.tex->width - 1;
	return (texture);
}

void	raycasting(t_cube3d *cube)
{
	t_ray_config	config;
	int				screen_x;

	config = init_ray_config(cube);
	screen_x = 0;
	while (screen_x < config.screen_width)
	{
		process_column(cube, screen_x, &config);
		screen_x++;
	}
}
