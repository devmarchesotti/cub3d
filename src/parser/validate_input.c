/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:58:04 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 07:02:40 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_file_content(char **file, int map_first_line, int *occurrences)
{
	int	i;

	i = 0;
	while (file[i] && i < map_first_line)
	{
		if (process_line(file[i], occurrences, i + 1))
			return (1);
		i++;
	}
	return (0);
}

int	initialize_occurrences(int *occurrences)
{
	occurrences[0] = 0;
	occurrences[1] = 0;
	occurrences[2] = 0;
	occurrences[3] = 0;
	occurrences[4] = 0;
	occurrences[5] = 0;
	return (0);
}

int	validate_file_structure(char **file, int *map_first_line)
{
	int	i;

	if (!file || !file[0])
	{
		ft_error("Error\nFile is empty or invalid.\n");
		return (1);
	}
	i = 0;
	while (file[i])
	{
		if (!is_empty_or_spaces(file[i]))
			break ;
		i++;
	}
	if (!file[i])
	{
		ft_error("Error\nFile contains only empty lines or spaces.\n");
		return (1);
	}
	*map_first_line = find_first_map_line(file);
	return (0);
}

int	check_lines(char **file)
{
	int	map_first_line;
	int	occurrences[6];
	int	i;

	if (validate_file_structure(file, &map_first_line))
		return (1);
	initialize_occurrences(occurrences);
	if (check_file_content(file, map_first_line, occurrences))
		return (1);
	i = map_first_line + get_map_height(file, map_first_line);
	while (file[i])
	{
		if (!is_empty_or_spaces(file[i]))
		{
			ft_error("Error\nContent found after the map.\n");
			return (1);
		}
		i++;
	}
	return (0);
}
