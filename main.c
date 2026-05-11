#include "cub3D.h"

void	ft_put_background(t_map *map, int mini_width, int mini_height)
{
	int	i;
	int	j;

	i = 2;
	j = 2;
	while (i < mini_height - 2)
	{
		while (j < mini_width - 2)
		{
			mlx_pixel_put(map->mlx, map->win, i, j, 0xffffff);
			j++;
		}
		i++;
		j = 2;
	}
}
 
int	choose_colour(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == ' ')
		return (0xffffff); // blanco
	if (map[i][j] == '1')
		return (0x000000);
	return (0x000000);
}

void	ft_put_map(t_map *map, int map_width, int map_height) // do not use pixel...better to convert it to image somehow...
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("map_height %d\n", map_height);
	printf("map_width %d\n", map_width);
	while (i < map_height - 1)
	{
		while (j < map_width - 1)
		{
			mlx_pixel_put(map->mlx, map->win, i, j, choose_colour(map->grid, map_height, map_width)); 
			j++;
		}
		i++;
		j = 0;
	}
}

void	put_minimap(t_map *map)
{
	int	mini_width;
	int	mini_height;

	mini_width = SCREEN_WIDTH / 6;
	mini_height = mini_width; // ????
	ft_put_background(map, mini_width, mini_height);
	//ft_put_map(map, mini_width,  mini_height);

}




int	ft_close_window(t_map *map)
{
	mlx_destroy_image(map->mlx, map->textures.no);
	mlx_destroy_image(map->mlx, map->textures.so);
	mlx_destroy_image(map->mlx, map->textures.we);
	mlx_destroy_image(map->mlx, map->textures.ea);
	mlx_destroy_window(map->mlx, map->win);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	destroy_map(map);
	exit(0);
}


static int	handle_no_event(void)
{
	return (0);
}


int	main(int ac, char **av)
{
	t_map	*map;
	int		fd;

	if (ac != 2)
	{
		write (1, "Usage: ./cub3D map.cub\n", 24);
		return (1);
	}
	if (!ft_format(av[1]))
	{
		write(1, "Correct format is .cub\n", 24);
		return (1);
	}
	map = init_map();
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	if (!parse_file(fd, map))
	{
		printf("Some mistakes in the textures\n");
		close(fd);
		return (1);
	}
	debug(map);
	printf("Correct file!\n");

	//start_mini_map(map); 

	map->mlx = mlx_init();

	// 
	//map->win_width  = 30;
	//map->win_height = 15;

	map->win_width = map->max_cols * TILE_LEN;
	map->win_height = map->total_rows * TILE_LEN;
	/*if (map->mlx == NULL)
	//free all here!!!
		exit (1); */
	map->win = mlx_new_window(map->mlx, map->win_width,
			map->win_height, "cub3D");
	put_minimap(map);
	mlx_loop_hook(map->mlx, &handle_no_event, map);
	
	mlx_hook(map->win, 17, 0, &ft_close_window, map);
	//mlx_key_hook(map.win, &handle_input, map);
	mlx_loop(map->mlx);



	destroy_map(map);
	close(fd);
	return (0);
}
