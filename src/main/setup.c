/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:52:32 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 19:19:02 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_window(t_cube3d *cube3d)
{
	cube3d->window = malloc(sizeof(t_window));
	if (!cube3d->window)
		return (1);
	cube3d->window->width = WIDTH;
	cube3d->window->height = HEIGHT;
	cube3d->window->title = ft_strdup("CUBE3D");
	if (!cube3d->window->title)
		return (1);
	return (0);
}

int	init_player(t_cube3d *cube3d)
{
	cube3d->player = malloc(sizeof(t_player));
	if (!cube3d->player)
		return (1);
	cube3d->player->direction = cube3d->map->orientation;
	cube3d->player->x = cube3d->map->start_x + 0.5;
	cube3d->player->y = cube3d->map->start_y + 0.5;
	return (0);
}

int	init_mouse(t_cube3d *cube3d)
{
	cube3d->mousse = malloc(sizeof(t_mousse));
	if (!cube3d->mousse)
		return (1);
	cube3d->mousse->initialized = false;
	cube3d->mousse->enabled = true;
	cube3d->mousse->sensibilite = 0.002;
	return (0);
}

//ADD this for info: 
// printf_all_arg(*cube3d);

int	setup_cube3d(t_cube3d **cube3d, int argc, char **argv)
{
	*cube3d = malloc(sizeof(t_cube3d));
	if (!*cube3d)
		return (ft_error("Error\nMalloc failed\n"));
	if (init_window(*cube3d) != 0)
		ft_exit(*cube3d, "Error\nFailed to initialize window\n", 1);
	if (parser(argc, argv, *cube3d) != 0)
		ft_exit(*cube3d, NULL, 1);
	if (init_player(*cube3d) != 0)
		ft_exit(*cube3d, "Error\nFailed to initialize player\n", 1);
	if (init_mouse(*cube3d) != 0)
		ft_exit(*cube3d, "Error\nFailed to initialize mousse\n", 1);
	return (0);
}

int	setup_mlx(t_cube3d *cube3d)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(cube3d->window->width, cube3d->window->height, \
					cube3d->window->title, true);
	if (!mlx)
		return (ft_error("Error\nFailed to initialize MLX\n"));
	image = mlx_new_image(mlx, cube3d->window->width, cube3d->window->height);
	if (!image)
	{
		mlx_terminate(mlx);
		return (ft_error("Error\nFailed to create image\n"));
	}
	cube3d->image = image;
	cube3d->mlx = mlx;
	return (0);
}
