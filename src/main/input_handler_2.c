/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:05:04 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 07:19:36 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_mouse_rotation(double xpos, double ypos, void *param)
{
	t_cube3d	*c;

	c = (t_cube3d *)param;
	(void)ypos;
	(void)xpos;
	if (!c->mousse->initialized)
		c->mousse->initialized = true;
}

void	handle_mouse(t_cube3d *c)
{
	mlx_t	*mlx;
	int32_t	mouse_x;
	int32_t	mouse_y;
	int		center_x;
	double	delta_x;

	mlx = c->mlx;
	if (c->mousse->enabled && c->mousse->initialized)
	{
		mlx_get_mouse_pos(mlx, &mouse_x, &mouse_y);
		center_x = c->window->width / 2;
		delta_x = mouse_x - center_x;
		if (delta_x != 0)
		{
			c->player->direction += delta_x * c->mousse->sensibilite;
			if (c->player->direction < 0)
				c->player->direction += 2 * M_PI;
			else if (c->player->direction >= 2 * M_PI)
				c->player->direction -= 2 * M_PI;
			mlx_set_mouse_pos(mlx, center_x, c->window->height / 2);
		}
	}
}

void	hook_esc(mlx_key_data_t keydata, void *param)
{
	t_cube3d	*c;

	c = (t_cube3d *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(c->mlx);
	}
	else if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		c->mousse->enabled = !c->mousse->enabled;
		if (c->mousse->enabled)
			mlx_set_cursor_mode(c->mlx, MLX_MOUSE_HIDDEN);
		else
			mlx_set_cursor_mode(c->mlx, MLX_MOUSE_NORMAL);
	}
}

void	on_resize(int32_t width, int32_t height, void *param)
{
	t_cube3d	*c;

	c = (t_cube3d *)param;
	c->window->width = width;
	c->window->height = height;
	if (c->image)
		mlx_delete_image(c->mlx, c->image);
	c->image = mlx_new_image(c->mlx, width, height);
	if (!c->image)
	{
		ft_error("Error\nImpossible to create a new image.\n");
		mlx_close_window(c->mlx);
		return ;
	}
	mlx_image_to_window(c->mlx, c->image, 0, 0);
	raycasting(c);
}
