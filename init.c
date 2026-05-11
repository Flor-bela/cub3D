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
	map->grid = NULL;
	map->total_rows = 0;
	return (map);
}

void	destroy_map(t_map *map)
{
	int	i;

	i = 0;
	free(map->textures.no);
	free(map->textures.so);
	free(map->textures.we);
	free(map->textures.ea);
	if(map->grid)
	{
		while(i < map->total_rows)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

static void	texture_load(t_map *map, void **img, char *path)
{
	int	len;

	len = TILE_LEN;
	*img = mlx_xpm_file_to_image(map->mlx, path, &len, &len);
	if (*img == 0)
		errormsg("texture_init(): can't load texture", errno);
}

void	img_init(t_map *map)
{
	map->img = (t_img *)malloc(sizeof(t_img));
//	if (!map->img)
//		base_destroy(map, "img_init(): malloc()", errno);
	map->img->no = 0;
	map->img->so = 0;
	map->img->we = 0;
	map->img->ea = 0;
	texture_load(map, &map->img->no, map->textures.no);
	texture_load(map, &map->img->so, map->textures.so);
	texture_load(map, &map->img->we, map->textures.we);
	texture_load(map, &map->img->ea, map->textures.ea);
}

/*void	start_game(t_map *map)
{
	map->win_width = map->map->width * TILE_LEN;
	map->win_height = map->map->height * TILE_LEN;
	map->mlx = mlx_init();
	if (map->mlx == NULL)
		exit (1);
	map->win = mlx_new_window(map->mlx, map->win_width,
			map->win_height, "This is Fine");
	if (map->win == NULL)
	{
		mlx_destroy_display(base->mlx);
		free(base->mlx);
		exit (1);
	}
}*/
