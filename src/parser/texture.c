/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:03:30 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/21 13:45:21 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_texture_field(t_textures *textures, char *identifier, char *value)
{
	if (ft_strncmp(identifier, "NO", 2) == 0)
		textures->no = ft_strdup(value);
	else if (ft_strncmp(identifier, "SO", 2) == 0)
		textures->so = ft_strdup(value);
	else if (ft_strncmp(identifier, "WE", 2) == 0)
		textures->we = ft_strdup(value);
	else if (ft_strncmp(identifier, "EA", 2) == 0)
		textures->ea = ft_strdup(value);
}

int	no_texture(t_textures *textures, char *identifier)
{
	set_texture_field(textures, identifier, "");
	ft_putstr_fd("Error\nTexture for ", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd(" not found\n", 2);
	return (1);
}

int	get_texture(t_textures *textures, char **file, char *identifier)
{
	char	**split;
	int		i;
	char	*trimmed_path;

	i = 0;
	while (file[i])
	{
		if (ft_strnstr(file[i], identifier, ft_strlen(identifier)))
		{
			split = ft_split(file[i], ' ');
			if (ft_strncmp(identifier, split[0], ft_strlen(split[0])) == 0 \
				&& split[1])
			{
				trimmed_path = ft_strtrim(split[1], " \t\n\v\f\r");
				set_texture_field(textures, identifier, trimmed_path);
				free(trimmed_path);
				free_split(split);
				return (0);
			}
			free_split(split);
		}
		i++;
	}
	return (no_texture(textures, identifier));
}

int	check_texture_extension(t_textures *textures)
{
	if (!ft_strnstr(textures->no + (ft_strlen(textures->no) - 4), ".png", 4) || \
		!ft_strnstr(textures->so + (ft_strlen(textures->so) - 4), ".png", 4) || \
		!ft_strnstr(textures->we + (ft_strlen(textures->we) - 4), ".png", 4) || \
		!ft_strnstr(textures->ea + (ft_strlen(textures->ea) - 4), ".png", 4))
	{
		ft_putstr_fd("Error\nTexture extension must be .png\n", 2);
		return (1);
	}
	return (0);
}

int	parse_texture(t_textures *textures, char **file)
{
	int	error;

	error = 0;
	error |= get_texture(textures, file, "NO");
	error |= get_texture(textures, file, "SO");
	error |= get_texture(textures, file, "WE");
	error |= get_texture(textures, file, "EA");
	if (error)
		return (error);
	if (check_texture_access(textures))
		return (1);
	if (check_texture_extension(textures))
		return (1);
	if (load_textures(textures))
		return (1);
	return (0);
}
