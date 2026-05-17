/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:48:35 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/15 15:52:18 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_map(char **line, t_game *game, int fd)
{
	char	*temp;

	temp = ft_calloc(1, 1);
	while (*line && empty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
		continue ;
	}
	while (*line)
	{
		temp = ft_strjoin_free(temp, *line);
		game->map.total_row++;
		free(*line);
		*line = get_next_line(fd);
	}
	game->map.grid = ft_split(temp, '\n');
	free(temp);
	if (!check_characters_map(game))
		return (0);
	if (!check_map_enclosed(game))
		return (0);
	return (1);
}

int	parse_color(char **line, t_game *game, int fd)
{
	while (*line)
	{
		if (empty_line(*line))
		{
			free(*line);
			*line = get_next_line(fd);
			continue ;
		}
		if (!is_color_line(*line))
			break ;
		if (!extract_color(*line, game))
			return (0);
		free(*line);
		*line = get_next_line(fd);
	}
	if (!all_colors_found(game))
		return (0);
	return (1);
}

int	parse_texture(char **line, t_game *game, int fd)
{
	*line = get_next_line(fd);
	while (*line)
	{
		if (empty_line(*line))
		{
			free(*line);
			*line = get_next_line(fd);
			continue ;
		}
		if (!is_texture_line(*line))
			break ;
		if (!extract_texture(*line, game))
			return (0);
		free(*line);
		*line = get_next_line(fd);
	}
	if (!all_textures_found(game))
		return (0);
	return (1);
}

int	parse_file(int fd, t_game *game)
{
	char	*line;

	line = NULL;
	if (!parse_texture(&line, game, fd)) // Saltar líneas vacías, comprobar que no se repiten ni faltan y tienen el formato correcto
	{
		close(fd);
		free(line);
		game_destroy(game, "The textures are not correct", errno);
	}
	if (!parse_color(&line, game, fd)) // Saltar líneas vacías, comprobar que no se repiten ni faltan y tienen el formato correcto
	{
		close(fd);
		free(line);
		game_destroy(game, "The colors are not correct", errno);
	}
	if (!parse_map(&line, game, fd)) // Comprobar que el mapa está cerrado y tiene solo los caracteres correctos (1, 0 y posición de personaje)
	{
		close(fd);
		free(line);
		game_destroy(game, "The map is not correct", errno);
	}
	player_direction(game);
	return (1);
}
