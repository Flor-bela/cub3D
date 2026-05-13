#include "cub3D.h"

void	ft_mlx_pixel_put(t_mini *img, int x, int y, int colour)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)); // por 8 para convertirlo en bits
	*(int*)dst = colour;
}

void	draw_square(t_mini *img, int x, int y, int size, int colour)
{
	int i = 0;
	int j;

	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_mlx_pixel_put(img, x + j, y + i, colour);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_map *map)
{
	t_mini	mini_map;
	int		y = 0; // rows
	int		x; // cols
	int		tile = 10; // Tamaño de cada cuadro en el minimapa 
	int		colour;

	mini_map.img_ptr = mlx_new_image(map->mlx, map->max_cols * tile, map->total_rows * tile);
	mini_map.addr = mlx_get_data_addr(mini_map.img_ptr, &mini_map.bits_per_pixel, &mini_map.line_length, &mini_map.endian);

	while (y < map->total_rows)
	{
		x = 0;
		while (x < map->max_cols)
		{
			if (map->grid[y][x] == '1')
				colour = 0x000000;
			else if (map->grid[y][x] == '0')
				colour = 0xFFFFFF; 
			else if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' || map->grid[y][x] == 'W' || map->grid[y][x] == 'E')
				colour = 0x00FF00; // verde
			else
				colour = 0x808080; // gris?? para los espacios sin nada
			draw_square(&mini_map, x * tile, y * tile, tile, colour);
			x++;
		}
		y++;
	}

	//mini mapa en el rincón izquierdo? 20, 20 -> posicion
	mlx_put_image_to_window(map->mlx, map->win, mini_map.img_ptr, 20, 20);

	
	//mlx_destroy_image(map->mlx, mini_map.img_ptr); // quizás ponerla en t_map....??
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

	

	map->mlx = mlx_init();
	map->win_width = map->max_cols * TILE_LEN;
	map->win_height = map->total_rows * TILE_LEN;
	/*if (map->mlx == NULL)
	//free all here!!!
		exit (1); */
	map->win = mlx_new_window(map->mlx, map->win_width,
			map->win_height, "cub3D");
	
	mlx_loop_hook(map->mlx, &handle_no_event, map);
	render_minimap(map);
	mlx_hook(map->win, 17, 0, &ft_close_window, map);
	//mlx_key_hook(map.win, &handle_input, map);
	mlx_loop(map->mlx);



	destroy_map(map);
	close(fd);
	return (0);
}
