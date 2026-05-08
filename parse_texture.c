#include "cub3D.h"

int	save_path(char *path, char **texture)
{
	if (*texture)
	{
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

int	parse_texture(char *line, t_map *map)
{
	char	*path;

	while (ft_isspace(*line))
		line++;
	path = extract_path(line + 2);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (save_path(path, &map->textures.no));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (save_path(path, &map->textures.so));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (save_path(path, &map->textures.we));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (save_path(path, &map->textures.ea));
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
