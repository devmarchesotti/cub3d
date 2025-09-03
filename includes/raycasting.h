/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:50:22 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 21:05:34 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3D.h"

/**
 * @struct s_dda
 * @brief Represents the data required for Digital Differential Analysis (DDA).
 * 
 * This structure is used to calculate the intersection of rays with 
 * the grid cells in a 2D map.
 * It contains information about the current position in the map, the direction 
 * of the ray, and the distances required for stepping through the grid.
 */
typedef struct s_dda
{
	int		map_pos_x;
	int		map_pos_y;
	int		step_x;
	int		step_y;
	int		side;
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
}	t_dda;

/**
 * struct s_ray - Represents a ray used in raycasting calculations.
 * cam_x: The camera's X-coordinate in normalized space (-1 to 1).
 * dir: The direction of the ray in the scene.
 *
 **/
typedef struct s_ray
{
	float	cam_x;
	float	dir;
}	t_ray;

// Represents a vertical slice of the screen for raycasting rendering.
typedef struct s_slice
{
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_slice;

// Parameters for rendering a vertical column (slice) of a wall
typedef struct s_render_params
{
	int				column;
	int				screen_height;
	int				wall_start;
	int				wall_end;
	int				wall_height;
	mlx_texture_t	*wall_texture;
	int				texture_x;
}	t_render_params;

/**
 * - tex: Pointer to the texture object (mlx_texture_t).
 * - x_cord_text: X-coordinate of the texture.
 * - inter_wall_x: Floating-point value representing the wall 
 * 			intersection in texture space.
 */
typedef struct s_texinfo
{
	mlx_texture_t	*tex;
	int				x_cord_text;
	float			inter_wall_x;
}	t_texinfo;

//Configuration parameters for raycasting
typedef struct s_ray_config
{
	int		screen_width;
	int		screen_height;
	float	half_fov;
}	t_ray_config;

//DDA
void			initialize_dda_algorithm(t_player *player, \
							float ray_direction, t_dda *dda);
void			perform_dda(t_cube3d *cube, t_dda *d);

//DRAWING
void			draw_slice(t_cube3d *cube, mlx_image_t *image, \
							t_render_params *params);

//RAY PROCESSOR
t_ray_config	init_ray_config(t_cube3d *cube);
void			process_column(t_cube3d *cube, int screen_x, \
								t_ray_config *config);

//RAY CALCULATION
float			distance_fish_eye(float cam_x, float halfF, t_dda *dda);
t_ray			compute_ray(int x, int w, float halfF, t_player *p);

//RAYCASTING
t_slice			compute_slice(int h, float perpDist);
t_texinfo		select_texture_info(t_cube3d *c, t_player *p, \
										t_dda *d, float perpDist);
void			raycasting(t_cube3d *cube);

#endif