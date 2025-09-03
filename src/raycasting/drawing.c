/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:31:01 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 21:18:24 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

uint32_t	get_ceiling_color(t_cube3d *c)
{
	return ((c->ceiling->red << 24) \
			| (c->ceiling->green << 16) \
			| (c->ceiling->blue << 8) \
			| 0xFF);
}

uint32_t	get_floor_color(t_cube3d *c)
{
	return ((c->floor->red << 24) \
			| (c->floor->green << 16) \
			| (c->floor->blue << 8) \
			| 0xFF);
}

uint32_t	get_texture_pixel_color(mlx_texture_t *texture, \
									int x_cord_text, int texY)
{
	size_t	bytes_per_pixel;
	size_t	index;
	size_t	total_pixels;
	uint8_t	*pixel_data;

	bytes_per_pixel = texture->bytes_per_pixel;
	index = (size_t)texY * texture->width * bytes_per_pixel \
			+ (size_t)x_cord_text * bytes_per_pixel;
	total_pixels = (size_t)texture->width * texture->height * bytes_per_pixel;
	if (index + bytes_per_pixel > total_pixels)
	{
		index = total_pixels - bytes_per_pixel;
	}
	pixel_data = &texture->pixels[index];
	return ((pixel_data[0] << 24) | (pixel_data[1] << 16) | \
			(pixel_data[2] << 8) | pixel_data[3]);
}

uint32_t	get_pixel_color(t_cube3d *cube, t_render_params *params, \
							int screen_y)
{
	int			tex_y;
	int			distance_from_top;

	if (screen_y < params->wall_start)
		return (get_ceiling_color(cube));
	else if (screen_y <= params->wall_end)
	{
		distance_from_top = screen_y - (params->screen_height / 2 \
					- params->wall_height / 2);
		tex_y = (distance_from_top * params->wall_texture->height) / \
					params->wall_height;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= (int)params->wall_texture->height)
			tex_y = params->wall_texture->height - 1;
		return (get_texture_pixel_color(params->wall_texture, \
				params->texture_x, tex_y));
	}
	else
		return (get_floor_color(cube));
}

void	draw_slice(t_cube3d *cube, mlx_image_t *image, t_render_params *params)
{
	int			screen_y;
	uint32_t	pixel_color;

	screen_y = 0;
	while (screen_y < params->screen_height)
	{
		pixel_color = get_pixel_color(cube, params, screen_y);
		mlx_put_pixel(image, params->column, screen_y, pixel_color);
		screen_y++;
	}
}
