#include "cub3D.h"

void	debug(t_map *map)
{
	printf("NO: %s\n", map->textures.no);
	printf("SO: %s\n", map->textures.so);
	printf("WE: %s\n", map->textures.we);
	printf("EA: %s\n", map->textures.ea);
	printf("Floor: %d - %d - %d\n", map->colors.floor[0], map->colors.floor[1], map->colors.floor[2]);
	printf("Ceiling: %d - %d - %d\n", map->colors.ceiling[0], map->colors.ceiling[1], map->colors.ceiling[2]);
}