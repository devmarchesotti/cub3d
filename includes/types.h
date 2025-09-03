/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:15:55 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 21:11:59 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * This header file contains the definitions of structures that represent
 * textures, colors, the game map, and the overall game state.
 */

#ifndef TYPES_H
# define TYPES_H

# include "../libs/MLX42/include/MLX42/MLX42.h"

# define MOVE_SPEED 0.10f
# define ROT_SPEED  0.03f
# define SPRINT_FACTOR 2.25f
# define WIDTH 1560
# define HEIGHT 780

/*
 * This structure holds the file paths for the north, south, west, 
 * and east wall, textures, as well as the floor and ceiling textures.
 */
typedef struct s_textures
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*f;
	char			*c;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
}	t_textures;

/*
 * This structure is used to define colors for the ceiling and floor.
 */

typedef struct s_colors
{
	int	red;
	int	green;
	int	blue;
}	t_colors;

/*
* This structure holds the 2D map layout, its dimensions, and the player's
 * starting position and orientation.
 *
 * Initial orientation of the player:
 * - 0: North
 * - 1: East
 * - 2: South
 * - 3: West
 */

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	float	orientation;
}	t_map;

/*
 * This structure represents the player, including their position
 * in the game world as floating-point coordinates and the direction
 * they are facing, represented as an integer.
 */
typedef struct s_player
{
	float	x;
	float	y;
	float	direction;
}	t_player;

/*
 * This structure holds information about the game window, including its
 * width, height, and title.
 */
typedef struct s_window
{
	int		width;
	int		height;
	char	*title;
}	t_window;

/*
 * This structures holds information on the mousse position 
 * (only the x to see where to steer). 
 * Also keep in memory if the mousse can be use to change direction.
*/
typedef struct s_mousse
{
	double	prev_x;
	double	curr_x;
	bool	initialized;
	bool	enabled;
	float	sensibilite;
}	t_mousse;

/*
 * This structure encapsulates all the data required for the game, including
 * textures, ceiling and floor colors, and the map.
 */
typedef struct s_cube3d
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	t_textures	*textures;
	t_colors	*ceiling;
	t_colors	*floor;
	t_map		*map;
	t_window	*window;
	t_player	*player;
	t_mousse	*mousse;
}	t_cube3d;

#endif