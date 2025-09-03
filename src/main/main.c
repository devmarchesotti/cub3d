/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:01:24 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 07:08:34 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	setup_hooks(t_cube3d *cube3d)
{
	mlx_image_to_window(cube3d->mlx, cube3d->image, 0, 0);
	mlx_cursor_hook(cube3d->mlx, &handle_mouse_rotation, cube3d);
	mlx_loop_hook(cube3d->mlx, &handle_input, cube3d);
	mlx_key_hook(cube3d->mlx, &hook_esc, cube3d);
	mlx_resize_hook(cube3d->mlx, on_resize, cube3d);
	mlx_set_cursor_mode(cube3d->mlx, MLX_MOUSE_HIDDEN);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube3d	*cube3d;

	if (setup_cube3d(&cube3d, argc, argv))
		return (1);
	if (setup_mlx(cube3d))
	{
		free_all(cube3d);
		return (1);
	}
	raycasting(cube3d);
	if (setup_hooks(cube3d) != 0)
	{
		mlx_terminate(cube3d->mlx);
		free_all(cube3d);
		return (1);
	}
	mlx_loop(cube3d->mlx);
	mlx_terminate(cube3d->mlx);
	free_all(cube3d);
	return (0);
}
