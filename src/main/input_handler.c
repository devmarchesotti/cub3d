/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:24:31 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 07:28:27 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	can_move(t_cube3d *c, float x, float y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (my < 0 || my >= c->map->height || mx < 0 || mx >= c->map->width)
		return (false);
	return (c->map->map[my][mx] != '1');
}

static void	rotate(t_cube3d *c, bool left)
{
	float	window_factor;

	window_factor = (float)c->window->width / WIDTH;
	if (left)
		c->player->direction -= ROT_SPEED * window_factor;
	else
		c->player->direction += ROT_SPEED * window_factor;
	if (c->player->direction < 0)
		c->player->direction += 2 * M_PI;
	else if (c->player->direction >= 2 * M_PI)
		c->player->direction -= 2 * M_PI;
}

void	move_side(t_cube3d *c, bool left)
{
	float	dir;
	float	nx;
	float	ny;
	float	current_speed;

	if (left)
		dir = c->player->direction - M_PI / 2;
	else
		dir = c->player->direction + M_PI / 2;
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT_SHIFT))
		current_speed = MOVE_SPEED * SPRINT_FACTOR;
	else
		current_speed = MOVE_SPEED;
	nx = c->player->x + cosf(dir) * current_speed;
	ny = c->player->y + sinf(dir) * current_speed;
	if (can_move(c, nx, c->player->y))
		c->player->x = nx;
	if (can_move(c, c->player->x, ny))
		c->player->y = ny;
}

void	move(t_cube3d *c, bool forward)
{
	float	dir;
	float	nx;
	float	ny;
	float	move_factor;
	float	current_speed;

	dir = c->player->direction;
	if (forward)
		move_factor = 1.0f;
	else
		move_factor = -1.0f;
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT_SHIFT))
		current_speed = MOVE_SPEED * SPRINT_FACTOR * \
					(float)c->window->width / WIDTH;
	else
		current_speed = MOVE_SPEED * (float)c->window->width / WIDTH;
	nx = c->player->x + cosf(dir) * current_speed * move_factor;
	ny = c->player->y + sinf(dir) * current_speed * move_factor;
	if (can_move(c, nx, c->player->y))
		c->player->x = nx;
	if (can_move(c, c->player->x, ny))
		c->player->y = ny;
}

void	handle_input(void *param)
{
	t_cube3d	*c;
	mlx_t		*mlx;

	c = param;
	mlx = c->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move(c, true);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move(c, false);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_side(c, true);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_side(c, false);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate(c, true);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate(c, false);
	handle_mouse(c);
	raycasting(c);
}
