#include "cub3D.h"

static void	draw_tile_at(t_map *map, int x, int y)
{
	char	tile;

	tile = map->grid[y][x];
	if (tile == '0')
		mlx_put_image_to_window(map->mlx, map->win,
			map->img->no, TILE_LEN * x, TILE_LEN * y);
	if (tile == '1')
		mlx_put_image_to_window(map->mlx, map->win,
			map->img->so, TILE_LEN * x, TILE_LEN * y);
	else if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		mlx_put_image_to_window(map->mlx, map->win,
			map->img->we, TILE_LEN * x, TILE_LEN * y);
}

void	render_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->total_rows)
	{
		x = 0;
		while (x < map->total_colums)
		{
			draw_tile_at(map, x, y);
			x++;
		}
		y++;
	}
}