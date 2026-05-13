#include "cub3D.h"

int	all_colors_found(t_map *map)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (map->colors.floor[i] < 0 || map->colors.floor[i] > 255
			|| map->colors.ceiling[i] < 0 || map->colors.ceiling[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

int	save_color(char *line, int *colors, int *ccolor)
{
	char	*temp;
	int		index;
	int		i;
	int		size;

	i = 0;
	index = 0;
	while (line[i])
	{
		while (line[i] && !ft_isdigit(line[i]))
			i++;
		size = i;
		while (line[size] && ft_isdigit(line[size]))
			size++;
		if (size - i > 0)
		{
			if (index > 2)
				return (0);
			temp = ft_substr(line, i, size);
			colors[index++] = ft_atoi(temp);
			free(temp);
		}
		i = size;
	}
	*ccolor = ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
	return (1);
}

int	extract_color(char *line, t_map *map)
{
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'F')
	{
		if (map->colors.floor[0] >= 0)
			return (0);
		return (save_color(line, map->colors.floor, &map->colors.f_color));
	}
	else if (*line == 'C')
	{
		if (map->colors.ceiling[0] >= 0 || map->colors.floor[0] < 0)
			return (0);
		return (save_color(line, map->colors.ceiling, &map->colors.c_color));
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
