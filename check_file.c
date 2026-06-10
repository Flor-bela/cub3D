/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:48:35 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/10 13:52:34 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_map(char **line, t_game *game, int fd)
{
	char	*temp;

	temp = ft_calloc(1, 1);
	while (*line && new_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
		continue ;
	}
	while (*line)
	{
		temp = ft_strjoin_free(temp, *line);
		free(*line);
		*line = get_next_line(fd);
	}
	game->map.grid = ft_split(temp, '\n');
	free(temp);
	update_total_row(game);
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
	if (!*line)
		game_destroy(game, "Empty file", 0);
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

/**
 * @brief Parses the game config. file including textures, colors, and the map.
 * @details This function skips empty lines and checks these rules:
 * - Exactly 4 unique textures with the correct format.
 * - Exactly 2 colors (RGB format).
 * - The map must only contain allowed characters ('1', '0', ' ', and the player
 * position that could be 'N', 'S', 'W' or 'E').
 * - The map must be fully enclosed.
 * @param fd The file descriptor of the opened file .cub to read from.
 * @param game Pointer to the main data structure.
 * @return int Return 1 if successful parsing. If it fails, it frees allocated
 * memory, closes the file, and terminates with game_destroy().
 */
int	parse_file(int fd, t_game *game)
{
	char	*line;

	line = NULL;
	if (!parse_texture(&line, game, fd))
	{
		free(line);
		close_file(fd);
		game_destroy(game, "The textures are not correct", errno);
	}
	if (!parse_color(&line, game, fd))
	{
		free(line);
		close_file(fd);
		game_destroy(game, "The colors are not correct", errno);
	}
	if (!parse_map(&line, game, fd))
	{
		close(fd);
		free(line);
		game_destroy(game, 0, errno);
	}
	player_direction(game);
	return (1);
}
