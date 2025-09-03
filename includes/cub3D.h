/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:15:51 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 07:19:07 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>

# include <math.h>

# include "types.h"

# include "libft.h"

# include "../libs/MLX42/include/MLX42/MLX42.h"

# include "parser.h"
# include "raycasting.h"

//FREE-DOM 1-2
void	free_split(char **split);
void	free_all(t_cube3d *cube3d);
void	free_map(t_map *map);
void	free_colors(t_colors *colors);
void	free_textures(t_textures *textures);

//TOOL BOX
void	ft_exit(t_cube3d *cube3d, char *str, int exit_code);
void	printf_all_arg(t_cube3d *cube3d);
int		ft_error(char *message);
void	print_map(char **map);
int		is_empty_or_spaces(const char *line);

//INPUT_HANDLER 1-2
void	handle_input(void *param);
void	hook_esc(mlx_key_data_t keydata, void *param);
void	hook_esc(mlx_key_data_t keydata, void *param);
void	handle_mouse(t_cube3d *c);
void	handle_mouse_rotation(double xpos, double ypos, void *param);
void	on_resize(int32_t width, int32_t height, void *param);

//SETUP
int		setup_mlx(t_cube3d *cube3d);
int		setup_cube3d(t_cube3d **cube3d, int argc, char **argv);

#endif