#include "cub3D.h"

int	ft_format(char *file)
{
	size_t	len;

	len = ft_strlen(file) - 1;
	if (file[len] == 'b' && file[len - 1] == 'u'
		&& file[len - 2] == 'c' && file[len - 3] == '.')
		return (1);
	return (0);
}

int	validate_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map->textures.no
		|| !map->textures.so
		|| !map->textures.we
		|| !map->textures.ea)
		return (0);
	while (i < 3)
	{
		if (map->colors.floor[i] < 0 || map->colors.floor[i] > 255
			|| map->colors.ceiling[i] < 0 || map->colors.ceiling[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

int	empty_line(char *line)
{
	if (!line)
		return (0);
	if (ft_isspace(*line) || *line == '\n')
	{
		line++;
		return (1);
	}
	return (0);
}

int	parse_file(int fd, t_map *map)
{
	char	*line;

	while ((1))
	{
		line = get_next_line(fd);
		if (is_texture_line(line))
		{
			if (!parse_texture(line, map))
				return (0);
		}
		else if (is_color_line(line))
		{
			if (!parse_color(line, map))
				return (0);
		}
		else if (empty_line(line))
			continue ;
		else
		{
			free (line);
			break ;
		}
		free(line);
	}
	return (validate_map(map));
}
