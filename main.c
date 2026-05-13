#include "cub3D.h"

int	expose_hook(void *param)
{
	t_map	*map;
	map = (t_map *)param;
	render_map(map);
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
		map_destroy(NULL, "Correct format is .cub", 0);
	map = init_map();
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		map_destroy(map, "File cannot be open", errno);
	parse_file(fd, map);
	debug(map);
	start_game(map);
	img_init(map);
	render_map(map);
	mlx_key_hook(map->win, handle_input, map);
	mlx_hook(map->win, 17, 0, close_game, map);
	mlx_expose_hook(map->win, expose_hook, map);
	mlx_loop(map->mlx);
	map_destroy(map, NULL, 0);
	close(fd);
	return (0);
}
