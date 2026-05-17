#include "cub3D.h"

int	check_characters_map(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (i < game->map.total_row) // hmmm tiene salto de línea!!!!! Tengo que quitarlo!!! No debería ser interpretado
	{
		j = 0;
		while (game->map.grid[i][j] != '\0')
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				 || game->map.grid[i][j] == 'W' || game->map.grid[i][j] == 'E')
			{
				game->player.p_x = j * TILE_SIZE;
				game->player.p_y = i * TILE_SIZE;
				game->player.pov = game->map.grid[i][j];
				flag++;
				j++;
			}
			else if (game->map.grid[i][j] == ' ' || game->map.grid[i][j] == '\n'
				|| game->map.grid[i][j] == '1' || game->map.grid[i][j] == '0')
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

int	error_walls(t_game *game)
{
	write(2, "Error \n map not enclosed by walls.\n", 36);
	(void)game;
	return (0);
}

int	check_map_enclosed(t_game *game)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	while (i < game->map.total_row)
	{
		j = 0;
		while (game->map.grid[i][j] != '\0')
		{
			if (game->map.grid[i][j] == '0')
			{
				flag = 0;
				if ((j + 1) < (int)ft_strlen(game->map.grid[i]))
				{
					flag++;
					if (game->map.grid[i][j + 1] == ' ' || game->map.grid[i][j + 1] == '\n')
						return (error_walls(game));
				}
				if ((j - 1) >= 0)
				{
					flag++;
					if (game->map.grid[i][j - 1] == ' ' || game->map.grid[i][j - 1] == '\n')
						return (error_walls(game));
				}
				if ((i - 1) >= 0)
				{	
					flag++;
					if (game->map.grid[i - 1][j] == ' ' || game->map.grid[i - 1][j] == '\n')
						return (error_walls(game));
				}
				if ((i + 1) < game->map.total_row)
				{
					flag++;
					if (game->map.grid[i + 1][j] == ' ' || game->map.grid[i + 1][j] == '\n')
						return (error_walls(game));
				}
				if (flag != 4)
					return (error_walls(game));
			}
			if(game->map.total_column < j)
				game->map.total_column = j;
			j++;
		}
		i++;
	}
	check_max_col(map); // lo añadi aqui quizas cambiar de sitio
	return (1);
}

