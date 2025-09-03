/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:52:20 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 21:04:15 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

/**
 * @brief Handle rendering logic for a single column
 * @param cube Structure containing game data
 * @param screen_x Current screen column
 * @param slice Pointer to slice data for rendering
 * @param tex_info Pointer to texture information
 */
void	process_rendering(t_cube3d *cube, int screen_x, t_slice *slice,
							t_texinfo *tex_info)
{
	t_render_params	render_params;

	render_params.column = screen_x;
	render_params.screen_height = cube->window->height;
	render_params.wall_start = slice->draw_start;
	render_params.wall_end = slice->draw_end;
	render_params.wall_height = slice->line_height;
	render_params.wall_texture = tex_info->tex;
	render_params.texture_x = tex_info->x_cord_text;
	draw_slice(cube, cube->image, &render_params);
}

/**
 * @brief Process a single column for raycasting
 * @param cube Structure containing game data
 * @param screen_x Current screen column
 * @param config Raycasting configuration
 */
void	process_column(t_cube3d *cube, int screen_x, t_ray_config *config)
{
	t_ray			ray;
	t_dda			dda;
	float			perpendicular_dist;
	t_slice			slice;
	t_texinfo		tex_info;

	ray = compute_ray(screen_x, config->screen_width, \
						config->half_fov, cube->player);
	initialize_dda_algorithm(cube->player, ray.dir, &dda);
	perform_dda(cube, &dda);
	perpendicular_dist = distance_fish_eye(ray.cam_x, config->half_fov, &dda);
	slice = compute_slice(config->screen_height, perpendicular_dist);
	tex_info = select_texture_info(cube, cube->player, &dda, \
			perpendicular_dist);
	process_rendering(cube, screen_x, &slice, &tex_info);
}

/**
 * @brief Initialize raycasting configuration
 * @param cube Structure containing game data
 * @return Raycasting configuration
 */
t_ray_config	init_ray_config(t_cube3d *cube)
{
	t_ray_config	config;

	config.screen_width = cube->window->width;
	config.screen_height = cube->window->height;
	config.half_fov = (60.0f * M_PI / 180.0f) * 0.5f;
	return (config);
}
