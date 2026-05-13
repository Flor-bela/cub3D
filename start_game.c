#include "cub3D.h"

void	start_game(t_map *map)
{
	map->win_width = map->total_rows * TILE_LEN;
	map->win_height = map->total_colums * TILE_LEN;
	map->mlx = mlx_init();
	if (map->mlx == NULL)
		map_destroy(map, "Fail to init mlx", errno);
	map->win = mlx_new_window(map->mlx, map->win_width,
			map->win_height, "Not Doom");
	if (map->win == NULL)
		map_destroy(map, "Fail to create new window", errno);
}