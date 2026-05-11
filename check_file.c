#include "cub3D.h"

int	parse_map(char **line, t_map *map, int fd)
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
		map->total_rows++;
		free(*line);
		*line = get_next_line(fd);
	}
	map->grid = ft_split(temp, '\n');
	free(temp);
	if (!check_characters_map(map))
		return (0);
	if (!check_map_enclosed(map))
		return (0);
	return (1);
}

int	parse_color(char **line, t_map *map, int fd)
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
		if (!extract_color(*line, map))
			return (0);
		free(*line);
		*line = get_next_line(fd);
	}
	if (!all_colors_found(map))
		return (0);
	return (1);
}

int	parse_texture(char **line, t_map *map, int fd)
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
		if (!extract_texture(*line, map))
			return (0);
		free(*line);
		*line = get_next_line(fd);
	}
	if (!all_textures_found(map))
		return (0);
	return (1);
}

int	parse_file(int fd, t_map *map)
{
	char	*line;

	line = NULL;
	if (!parse_texture(&line, map, fd)) // Saltar líneas vacías, comprobar que no se repiten ni faltan y tienen el formato correcto
	{
		destroy_map(map);
		return (0);
	}
	if (!parse_color(&line, map, fd)) // Saltar líneas vacías, comprobar que no se repiten ni faltan y tienen el formato correcto
	{
		destroy_map(map);
		return (0);
	}
	if (!parse_map(&line, map, fd)) // Comprobar que el mapa está cerrado y tiene solo los caracteres correctos (1, 0 y posición de personaje)
	{
		destroy_map(map);
		return (0);
	}
	return (1);
}
