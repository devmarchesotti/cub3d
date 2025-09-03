/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:15:03 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 06:48:45 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser(int argc, char **argv, t_cube3d *cube3d)
{
	char		**file;

	if (init_cub3d(cube3d))
		return (1);
	if (preliminary_checks(argc, argv) == 0)
		return (1);
	file = read_file_lines(argv[1]);
	if (!file)
		return (1);
	if (check_lines(file))
		return (1);
	if (parse_texture(cube3d->textures, file) || parse_color(cube3d, file) \
	|| parse_map(cube3d->map, file))
	{
		free_split(file);
		return (1);
	}
	free_split(file);
	return (0);
}
