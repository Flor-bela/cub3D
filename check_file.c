/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:48:35 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/30 17:40:55 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_empty_lines_map(char *temp)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!temp || temp[i] == '\0')
	{
		free(temp);
		write(2, "Error\nMap not found\n", 21);
		return (0);
	}
	while (temp[i] != '\0' && temp[i + 1] != '\0')
	{
		if (temp[i] == '\n' && temp[i + 1] == '\n')
			flag = 1;
		if (flag == 1 && temp[i] != '\0' && temp[i] != '\n')
		{
			free(temp);
			write(2, "Error\nIncorrect row on map\n", 28);
			return (0);
		}
		i++;
	}
	return (1);
}

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
	if (!check_empty_lines_map(temp))
		return (0);
	game->map.grid = ft_split(temp, '\n');
	free(temp);
	update_total_row(game);
	if (!check_characters_map(game))
		return (0);
	if (!check_map_enclosed(game))
		return (0);
	return (1);
}

int	parse_assets(char **line, t_game *game, int fd)
{
	while (*line)
	{
		while (empty_line(*line))
		{
			free(*line);
			*line = get_next_line(fd);
		}
		if (is_texture_line(*line))
		{
			if (!extract_texture(*line, game))
				return (0);
		}
		else if (is_color_line(*line))
		{
			if (!extract_color(*line, game))
				return (0);
		}
		else
			break ;
		free(*line);
		*line = get_next_line(fd);
	}
	if (!all_textures_found(game) || !all_colors_found(game))
		return (0);
	return (1);
}

/**
 * @brief Parses the game .cub file including textures, colors, and the map.
 * - This function skips empty lines and checks these rules:
 * - Exactly 4 unique textures with the correct format.
 * - Exactly 2 colors (RGB format).
 * - The map must only contain allowed characters ('1', '0', ' ', and the player
 * position that could be 'N', 'S', 'W' or 'E').
 * - The map must be fully enclosed.
 * @param fd The file descriptor of the opened file .cub to read from.
 * @param game Pointer to the main data structure.
 * @return int 1 if successful parsing. If it fails, it frees allocated
 * memory, closes the file, and terminates with game_destroy().
 */
int	parse_file(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	if (!*line)
	{
		game_destroy(game, "Empty file", 0);
		close (fd);
	}
	if (!parse_assets(&line, game, fd))
	{
		free(line);
		close_file(fd);
		game_destroy(game, "m", errno);
	}
	if (!parse_map(&line, game, fd))
	{
		close(fd);
		free(line);
		game_destroy(game, "m", errno);
	}
	player_direction(game);
	return (1);
}
