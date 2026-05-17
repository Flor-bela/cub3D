/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:07:45 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/15 16:07:45 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	all_textures_found(t_game *game)
{
	printf("Todas las texturas guardadsa?\n");
	return (game->map.text_path[NO]
		&& game->map.text_path[SO]
		&& game->map.text_path[WE]
		&& game->map.text_path[EA]);
}

int	save_path(char *path, char **texture)
{
	if (*texture)
	{
		printf("Textura ya usada\n");
		printf("%s\n", path);
		free(path);
		return (0);
	}
	*texture = path;
	return (1);
}

char	*extract_path(char *line)
{
	int	start;
	int	end;

	start = 0;
	while (ft_isspace(*line))
		line++;
	while (line[start] && ft_isspace(line[start]))
		start++;
	end = start;
	while (line[end] && line[end] != '\n')
		end++;
	return (ft_substr(line, start, end - start));
}

int	extract_texture(char *line, t_game *game)
{
	char	*path;

	while (ft_isspace(*line))
		line++;
	path = extract_path(line + 2);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (save_path(path, &game->map.text_path[NO]));
	else if (ft_strncmp(line, "SO", 2) == 0 && game->map.text_path[NO])
		return (save_path(path, &game->map.text_path[SO]));
	else if (ft_strncmp(line, "WE", 2) == 0 && game->map.text_path[SO])
		return (save_path(path, &game->map.text_path[WE]));
	else if (ft_strncmp(line, "EA", 2) == 0 && game->map.text_path[WE])
		return (save_path(path, &game->map.text_path[EA]));
	return (1);
}

int	is_texture_line(char *line)
{
	if (!line)
		return (0);
	while (ft_isspace(*line))
		line++;
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}
