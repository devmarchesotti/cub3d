/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:54:47 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/16 21:15:51 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	assign_color(int *color, char *color_split)
{
	int	value;

	value = ft_atoi(color_split);
	if (value >= 0 && value <= 255)
	{
		*color = value;
		return (1);
	}
	return (0);
}

int	split_color(t_colors *colors, char *color)
{
	char	**split;
	int		i;
	int		ret;

	split = ft_split(color, ',');
	if (!split)
	{
		ft_putstr_fd("Error\nSplit failed", 2);
		return (0);
	}
	i = 0;
	ret = 1;
	while (split[i])
	{
		if (i == 0)
			ret &= assign_color(&colors->red, split[i]);
		else if (i == 1)
			ret &= assign_color(&colors->green, split[i]);
		else if (i == 2)
			ret &= assign_color(&colors->blue, split[i]);
		i++;
	}
	free_split(split);
	return (ret);
}

int	is_valid_color(char *color)
{
	int		i;
	int		comma_count;

	i = 0;
	comma_count = 0;
	while (color[i])
	{
		if (color[i] == ',')
		{
			if (i > 0 && color[i - 1] == ',')
				return (0);
			if (i == 0)
				return (0);
			comma_count++;
		}
		else if (!ft_isdigit(color[i]) && color[i] != ' ' && color[i] != '\n')
			return (0);
		i++;
	}
	if (comma_count != 2)
		return (0);
	if (color[i - 1] == ',')
		return (0);
	return (1);
}

int	get_color(t_colors *colors, char **file, char *identifier)
{
	int		i;
	char	**split;

	i = 0;
	while (file[i])
	{
		if (ft_strnstr(file[i], identifier, ft_strlen(identifier)))
		{
			split = ft_split(file[i], ' ');
			if (ft_strncmp(split[0], identifier, ft_strlen(split[0])) == 0)
			{
				if (is_valid_color(split[1]) && split_color(colors, split[1]))
				{
					free_split(split);
					return (0);
				}
			}
			free_split(split);
		}
		i++;
	}
	ft_putstr_fd("Error\nColor for ", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd(" not found or not valid\n", 2);
	return (1);
}

int	parse_color(t_cube3d *cube3d, char **file)
{
	if (get_color(cube3d->ceiling, file, "C") == 1)
		return (1);
	if (get_color(cube3d->floor, file, "F") == 1)
		return (1);
	return (0);
}
