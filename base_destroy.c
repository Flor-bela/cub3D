#include "cub3D.h"

static void	map_destroy_images(t_map *map)
{
	if (!map->img)
		return ;
	if (map->img->no)
		mlx_destroy_image(map->mlx, map->img->no);
	if (map->img->so)
		mlx_destroy_image(map->mlx, map->img->so);
	if (map->img->ea)
		mlx_destroy_image(map->mlx, map->img->ea);
	if (map->img->we)
		mlx_destroy_image(map->mlx, map->img->we);
	free(map->img);
}

void	map_destroy(t_map *map, char *errmsg, int errnum)
{
	if (map)
	{
		if (map->img)
			map_destroy_images(map);
		if (map->mlx && map->win)
			mlx_destroy_window(map->mlx, map->win);
		if (map->mlx)
		{
			mlx_destroy_display(map->mlx);
			free(map->mlx);
		}
		free_map(map);
		free(map);
	}
	die(errmsg, errnum);
}

void	die(char *errmsg, int errnum)
{
	if (errmsg != 0 || errnum != 0)
		ft_putendl_fd("Error", 2);
	if (errmsg != 0)
		ft_putstr_fd(errmsg, 2);
	if (errmsg != 0 && errnum != 0)
		ft_putstr_fd(": ", 2);
	if (errnum != 0)
		ft_putstr_fd(strerror(errnum), 2);
	if (errmsg != 0 || errnum != 0)
	{
		ft_putendl_fd("", 2);
		exit(1);
	}
	exit(0);
}

int	close_game(t_map *map)
{
	ft_putendl_fd("¡Gracias por jugar!", 1);
	map_destroy(map, NULL, 0);
	exit (0);
}
