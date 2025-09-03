/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 06:57:44 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/23 07:03:05 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_double_occurrence(const char *identifier, int *occurrences)
{
	int	index;

	index = -1;
	if (!ft_strncmp(identifier, "NO", 2))
		index = 0;
	else if (!ft_strncmp(identifier, "EA", 2))
		index = 1;
	else if (!ft_strncmp(identifier, "SO", 2))
		index = 2;
	else if (!ft_strncmp(identifier, "WE", 2))
		index = 3;
	else if (!ft_strncmp(identifier, "F", 1))
		index = 4;
	else if (!ft_strncmp(identifier, "C", 1))
		index = 5;
	if (index != -1)
	{
		if (occurrences[index])
		{
			ft_error("Error\nDuplicate identifier.\n");
			return (1);
		}
		occurrences[index] = 1;
	}
	return (0);
}

int	is_valid_identifier(const char *identifier)
{
	return ((!ft_strncmp(identifier, "NO", 2)
			|| !ft_strncmp(identifier, "EA", 2)
			|| !ft_strncmp(identifier, "SO", 2)
			|| !ft_strncmp(identifier, "WE", 2)
			|| !ft_strncmp(identifier, "F", 1)
			|| !ft_strncmp(identifier, "C", 1))
		|| !ft_strncmp(identifier, "\n", 1));
}

int	process_line(char *line, int *occurrences, int line_nb)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line || !split_line[0])
	{
		ft_error("Error\nInvalid or empty line\n");
		return (1);
	}
	if (!is_valid_identifier(split_line[0]))
	{
		ft_error("Error\nUnknown identifier line ");
		ft_error(ft_itoa(line_nb));
		ft_error(".\n");
		free_split(split_line);
		return (1);
	}
	if (check_double_occurrence(split_line[0], occurrences))
	{
		free_split(split_line);
		return (1);
	}
	free_split(split_line);
	return (0);
}
