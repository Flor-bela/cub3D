/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:58:28 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/30 17:49:18 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	all_colors_found(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game->map.floor[i] < 0 || game->map.ceiling[i] < 0)
		{
			write(2, "Error\nMissing colours\n", 23);
			return (0);
		}
		if (game->map.floor[i] > 255 || game->map.ceiling[i] > 255)
		{
			write(2, "Error\nInvalid colours\n", 23);
			return (0);
		}
		i++;
	}
	return (1);
}

int	spaces(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == ','))
		i++;
	return (i);
}

int	save_color(char *line, int *colors, int *ccolor)
{
	int		index;
	int		i;

	index = 0;
	i = 1;
	while (line[i])
	{
		i = spaces(line, i);
		if (!ft_isdigit(line[i]))
			break ;
		if (index == 3)
		{
			write(2, "Error\nInvalid colour\n", 22);
			return (0);
		}
		colors[index++] = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
		i++;
	}
	*ccolor = ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
	return (1);
}

int	extract_color(char *line, t_game *game)
{
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'F')
	{
		if (game->map.floor[0] >= 0)
		{
			write(2, "Error\nDuplicate colour\n", 24);
			return (0);
		}
		return (save_color(line, game->map.floor, &game->map.f_color));
	}
	else if (*line == 'C')
	{
		if (game->map.ceiling[0] >= 0)
		{
			write(2, "Error\nDuplicate colour\n", 24);
			return (0);
		}
		return (save_color(line, game->map.ceiling, &game->map.c_color));
	}
	return (1);
}

int	is_color_line(char *line)
{
	if (!line)
		return (0);
	while (ft_isspace(*line))
		line++;
	return (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}
