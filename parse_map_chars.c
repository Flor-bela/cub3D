/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:06:29 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/09 19:07:13 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_each_char(t_game *game, int *flag, int row, int *col)
{
	printf("row %d, c is %c\n", row, game->map.grid[row][*col]);
	if (game->map.grid[row][0] == '\n' || game->map.grid[row][0] == '\0')
	{			
		write(2, "Error \n incorrect character on the map.\n", 41);
		return (0);
	}
	
	if (game->map.grid[row][*col] == 'N' || game->map.grid[row][*col] == 'S'
			|| game->map.grid[row][*col] == 'W'
			|| game->map.grid[row][*col] == 'E')
	{
		game->player.p_x = *col * TILE_SIZE + TILE_SIZE / 2;
		game->player.p_y = row * TILE_SIZE + TILE_SIZE / 2;
		game->player.pov = game->map.grid[row][*col];
		(*flag)++;
		(*col)++;
	}
	else if (game->map.grid[row][*col] == ' '
		|| game->map.grid[row][*col] == '1'
		|| game->map.grid[row][*col] == '\n'
		|| game->map.grid[row][*col] == '0')
		(*col)++;
	else
	{
		write(2, "Error \n incorrect character on the map.\n", 41);
		return (0);
	}
	return (1);
}

int	check_characters_map(t_game *game)
{
	int	row;
	int	col;
	int	flag;

	row = 0;
	flag = 0;
	while (row < game->map.total_row) // o sea.... no llega a row 10
	{
		col = 0;
		while (game->map.grid[row][col] != '\0') // aqui da segmentation fault....porque??? 
		{
			// nunca llega aqui a ir a row 14....
			printf("row here is %d\n", row);
			if (!check_each_char(game, &flag, row, &col))
				return (0);
		}
		if (game->map.total_column < col)
			game->map.total_column = col;
		row++;
	}
	if (flag != 1)
	{
		write(2, "Error \n incorrect starting point.\n", 35);
		return (0);
	}
	return (1);
}
