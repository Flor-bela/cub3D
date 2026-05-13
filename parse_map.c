#include "cub3D.h"

int	check_characters_map(t_map *map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (i < map->total_rows) // hmmm tiene salto de línea!!!!! Tengo que quitarlo!!! No debería ser interpretado
	{
		j = 0;
		while (map->grid[i][j] != '\0')
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				 || map->grid[i][j] == 'W' || map->grid[i][j] == 'E')
			{
				map->player.x = j;
				map->player.y = i;
				map->player.pov = map->grid[i][j];
				flag++;
				j++;
			}
			else if (map->grid[i][j] == ' ' || map->grid[i][j] == '\n'
				|| map->grid[i][j] == '1' || map->grid[i][j] == '0')
				j++;
			else
			{
				write(2, "Error \n incorrect character on the map.", 40);
				return (0);
			}
		}
		i++;
	}
	if (flag != 1)
	{
		write(2, "Error \n incorrect starting point.", 33);
		return (0);
	}
	return (1);
}

int	error_walls(t_map *map)
{
	write(2, "Error \n map not enclosed by walls.\n", 36);
	(void)map;
	return (0);
}

int	check_map_enclosed(t_map *map)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	while (i < map->total_rows)
	{
		j = 0;
		while (map->grid[i][j] != '\0')
		{
			if (map->grid[i][j] == '0')
			{
				flag = 0;
				if ((j + 1) < (int)ft_strlen(map->grid[i]))
				{
					flag++;
					if (map->grid[i][j + 1] == ' ' || map->grid[i][j + 1] == '\n')
						return (error_walls(map));
				}
				if ((j - 1) >= 0)
				{
					flag++;
					if (map->grid[i][j - 1] == ' ' || map->grid[i][j - 1] == '\n')
						return (error_walls(map));
				}
				if ((i - 1) >= 0)
				{	
					flag++;
					if (map->grid[i - 1][j] == ' ' || map->grid[i - 1][j] == '\n')
						return (error_walls(map));
				}
				if ((i + 1) < map->total_rows)
				{
					flag++;
					if (map->grid[i + 1][j] == ' ' || map->grid[i + 1][j] == '\n')
						return (error_walls(map));
				}
				if (flag != 4)
					return (error_walls(map));
			}
			if(map->total_colums < j)
				map->total_colums = j;
			j++;
		}
		i++;
	}
	return (1);
}