/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:06:29 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/11 16:49:37 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_each_char(t_game *game, int *flag, int row, int *col)
{
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
		write(2, "Error \nIncorrect character on the map.\n", 40);
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
	while (row < game->map.total_row)
	{
		col = 0;
		while (game->map.grid[row][col] != '\0')
		{
			if (!check_each_char(game, &flag, row, &col))
				return (0);
		}
		if (game->map.total_column < col)
			game->map.total_column = col;
		row++;
	}
	if (flag != 1)
	{
		write(2, "Error \nIncorrect starting point.\n", 34);
		return (0);
	}
	return (1);
}
