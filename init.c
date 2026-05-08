#include "cub3D.h"

t_map	*init_map(void)
{
	t_map	*map;
	int		i;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == 0)
		errormsg("base_init(): malloc()", errno);
	map->textures.no = NULL;
	map->textures.so = NULL;
	map->textures.we = NULL;
	map->textures.ea = NULL;
	i = 0;
	while (i < 3)
	{
		map->colors.ceiling[i] = -1;
		map->colors.floor[i] = -1;
		i++;
	}
	return (map);
}

void	destroy_map(t_map *map)
{
	free(map->textures.no);
	free(map->textures.so);
	free(map->textures.we);
	free(map->textures.ea);
	free(map);
}
