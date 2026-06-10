/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:06:29 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/09 12:06:50 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	error_walls(void)
{
	write(2, "Error \nMap not enclosed by walls.\n", 35);
	return (0);
}

static int	check_map_cols(int col, int row, int *flag, t_game *game)
{
	if ((col + 1) < (int)ft_strlen(game->map.grid[row]))
	{
		(*flag)++;
		if (game->map.grid[row][col + 1] == ' '
			|| game->map.grid[row][col + 1] == '\n')
			return (error_walls());
	}
	if ((col - 1) >= 0)
	{
		(*flag)++;
		if (game->map.grid[row][col - 1] == ' '
			|| game->map.grid[row][col - 1] == '\n')
			return (error_walls());
	}
	return (1);
}

static int	check_map_rows(int col, int row, int *flag, t_game *game)
{
	if ((row - 1) >= 0)
	{
		(*flag)++;
		if (game->map.grid[row - 1][col] == ' '
			|| game->map.grid[row - 1][col] == '\n')
			return (error_walls());
	}
	if ((row + 1) < game->map.total_row)
	{
		(*flag)++;
		if (game->map.grid[row + 1][col] == ' '
			|| game->map.grid[row + 1][col] == '\n')
			return (error_walls());
	}
	return (1);
}

static int	check_map(int col, int row, t_game *game)
{
	int	flag;

	flag = 0;
	if (!check_map_cols(col, row, &flag, game))
		return (0);
	if (!check_map_rows(col, row, &flag, game))
		return (0);
	if (flag != 4)
		return (error_walls());
	return (1);
}

int	check_map_enclosed(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map.total_row)
	{
		col = 0;
		while (game->map.grid[row][col] != '\0')
		{
			if (game->map.grid[row][col] == '0')
			{
				if (!check_map(col, row, game))
					return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}
