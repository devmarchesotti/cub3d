/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:15:42 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 07:00:55 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3D.h"
# define AUTHORIZED_MAP_CHARS " \t01NEWS\n"

//UTILS_1
int				preliminary_checks(int argc, char **argv);
int				init_cub3d(t_cube3d *cube3d);

//FILE READER
char			**read_file_lines(char *file_name);

//TEXTURE
int				parse_texture(t_textures *textures, char **file);

//TEXTURE 2
int				load_textures(t_textures *textures);
mlx_texture_t	*load_single_texture(char *path, char *identifier);
int				check_texture_access(t_textures *textures);

//COLOR
int				parse_color(t_cube3d *cube3d, char **file);

//MAP_UTILS_1
int				get_map_height(char	**file, int start_row);
int				get_map_width(char **file, int start_row, int end_row);
int				find_first_map_line(char **file);
int				is_authorized_char(char c);
int				is_map_line(const char *line);

//MAP_UTILS_2
int				is_map_valid(t_map *map);

//MAP
int				parse_map(t_map *map, char **file);

//VALIDATE 1-2
int				check_lines(char **file);
int				check_double_occurrence(const char *identifier, \
										int *occurrences);
int				is_valid_identifier(const char *identifier);
int				process_line(char *line, int *occurrences, int line_nb);

//PARSER
int				parser(int argc, char **argv, t_cube3d *cube3d);

#endif