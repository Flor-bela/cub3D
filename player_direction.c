#include "cub3D.h"

void	player_direction(t_map *map)
{
	if(map->player.pov == 'N')
	{
		map->player.dir_x = 0;
		map->player.dir_y = -1;
	}
	if(map->player.pov == 'S')
	{
		map->player.dir_x = 0;
		map->player.dir_y = 1;
	}
	if(map->player.pov == 'W')
	{
		map->player.dir_x = -1;
		map->player.dir_y = 0;
	}
	if(map->player.pov == 'E')
	{
		map->player.dir_x = 1;
		map->player.dir_y = 0;
	}
}
