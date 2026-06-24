/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:15:08 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/15 12:12:21 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(float x, float y, char **grid)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	valid_y(float map_x, float n_map_y, char **grid)
{
	if (is_wall(map_x, n_map_y + PLAYER_RADIUS, grid))
		return (0);
	if (is_wall(map_x, n_map_y - PLAYER_RADIUS, grid))
		return (0);
	if (is_wall(map_x + PLAYER_RADIUS, n_map_y, grid))
		return (0);
	if (is_wall(map_x - PLAYER_RADIUS, n_map_y, grid))
		return (0);
	return (1);
}

int	valid_x(float n_map_x, float map_y, char **grid)
{
	if (is_wall(n_map_x + PLAYER_RADIUS, map_y, grid))
		return (0);
	if (is_wall(n_map_x - PLAYER_RADIUS, map_y, grid))
		return (0);
	if (is_wall(n_map_x, map_y + PLAYER_RADIUS, grid))
		return (0);
	if (is_wall(n_map_x, map_y - PLAYER_RADIUS, grid))
		return (0);
	return (1);
}

// We validate x and y separately to allow sliding
void	valid_move(t_player *player, float x, float y, char **grid)
{
	int	n_map_x;
	int	n_map_y;

	n_map_x = player->p_x + x * SPEED;
	n_map_y = player->p_y + y * SPEED;
	if (valid_x(n_map_x, player->p_y, grid))
		player->p_x = n_map_x;
	if (valid_y(player->p_x, n_map_y, grid))
		player->p_y = n_map_y;
}
