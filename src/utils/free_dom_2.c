/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dom_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:22:55 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/21 14:25:34 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	free_textures(t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->no)
		free(textures->no);
	if (textures->so)
		free(textures->so);
	if (textures->we)
		free(textures->we);
	if (textures->ea)
		free(textures->ea);
	if (textures->no_texture)
		mlx_delete_texture(textures->no_texture);
	if (textures->so_texture)
		mlx_delete_texture(textures->so_texture);
	if (textures->we_texture)
		mlx_delete_texture(textures->we_texture);
	if (textures->ea_texture)
		mlx_delete_texture(textures->ea_texture);
	free(textures);
}

void	free_colors(t_colors *colors)
{
	if (!colors)
		return ;
	free(colors);
	colors = NULL;
}
