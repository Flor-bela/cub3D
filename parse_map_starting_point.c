/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_starting_point.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:56:46 by fda-roch          #+#    #+#             */
/*   Updated: 2026/06/26 16:58:56 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	error_starting_point(void)
{
	write(2, "Error \nIncorrect position for starting point.\n", 47);
	return (0);
}

static int	check_starting_point_row(t_game *game, int row, int col)
{
	if (row == game->map.total_row - 1 || row == 0)
		return (0);
	if ((row - 1) >= 0)
	{
		if (game->map.grid[row - 1][col] == ' '
			|| game->map.grid[row - 1][col] == '\n'
			|| !game->map.grid[row - 1][col])
			return (0);
	}
	if ((row + 1) < game->map.total_row)
	{
		if (game->map.grid[row + 1][col] == ' '
			|| game->map.grid[row + 1][col] == '\n'
			|| !game->map.grid[row + 1][col])
			return (0);
	}
	return (1);
}

static int	check_starting_point_col(t_game *game, int row, int col)
{
	if (col == ((int)ft_strlen(game->map.grid[row]) - 1) || col == 0)
		return (0);
	if ((col + 1) < (int)ft_strlen(game->map.grid[row]))
	{
		if (game->map.grid[row][col + 1] == ' '
			|| game->map.grid[row][col + 1] == '\n'
			|| !game->map.grid[row][col + 1])
			return (0);
	}
	if ((col - 1) >= 0)
	{
		if (game->map.grid[row][col - 1] == ' '
			|| game->map.grid[row][col - 1] == '\n'
			|| !game->map.grid[row][col + 1])
			return (0);
	}
	return (1);
}

int	check_starting_point_pos(t_game *game, int row, int col)
{
	if (!check_starting_point_row(game, row, col))
		return (error_starting_point());
	if (!check_starting_point_col(game, row, col))
		return (error_starting_point());
	if ((col + 1) < (int)ft_strlen(game->map.grid[row]))
	{
		if (game->map.grid[row][col + 1] == ' '
			|| game->map.grid[row][col + 1] == '\n'
			|| !game->map.grid[row][col + 1])
			return (error_starting_point());
	}
	if ((col - 1) >= 0)
	{
		if (game->map.grid[row][col - 1] == ' '
			|| game->map.grid[row][col - 1] == '\n'
			|| !game->map.grid[row][col + 1])
			return (error_starting_point());
	}
	return (1);
}
