#include "cub3D.h"

int	handle_input(int keysym, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (!map || !map->img)
	{
		map_destroy(map, "Error: imagen no iniciada", 0);
		return (1);
	}
	if (keysym == 65307)
	{
		close_game(map);
	}
	return (0);
}
