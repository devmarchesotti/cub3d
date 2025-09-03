/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:43:53 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/21 14:15:39 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_single_texture_access(char *path, char *identifier)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCan't access ", 2);
		ft_putstr_fd(identifier, 2);
		ft_putstr_fd(" texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_texture_access(t_textures *textures)
{
	char	*identifiers[4];
	char	*paths[4];
	int		error;
	int		i;

	identifiers[0] = "NO";
	identifiers[1] = "SO";
	identifiers[2] = "WE";
	identifiers[3] = "EA";
	paths[0] = textures->no;
	paths[1] = textures->so;
	paths[2] = textures->we;
	paths[3] = textures->ea;
	error = 0;
	i = 0;
	while (i < 4)
	{
		if (check_single_texture_access(paths[i], identifiers[i]))
			error = 1;
		i++;
	}
	return (error);
}

mlx_texture_t	*load_single_texture(char *path, char *identifier)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_putstr_fd("Error\nFailed to load ", 2);
		ft_putstr_fd(identifier, 2);
		ft_putstr_fd(" texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	return (texture);
}

int	load_textures(t_textures *textures)
{
	textures->no_texture = load_single_texture(textures->no, "NO");
	if (!textures->no_texture)
		return (1);
	textures->so_texture = load_single_texture(textures->so, "SO");
	if (!textures->so_texture)
		return (1);
	textures->we_texture = load_single_texture(textures->we, "WE");
	if (!textures->we_texture)
		return (1);
	textures->ea_texture = load_single_texture(textures->ea, "EA");
	if (!textures->ea_texture)
		return (1);
	return (0);
}
