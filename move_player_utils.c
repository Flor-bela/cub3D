/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:15:08 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/05 14:58:26 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(float x, float y, char **grid)
{
	int	mapx;
	int	mapy;

	mapx = x / TILE_SIZE;
	mapy = y / TILE_SIZE;
	if (grid[mapy][mapx] == '1')
		return (1);
	return (0);
}

int	valid_y(float mapx, float n_mapy, char **grid)
{
	if (is_wall(mapx, n_mapy + PLAYER_RADIUS, grid))
		return (0);
	if (is_wall(mapx, n_mapy - PLAYER_RADIUS, grid))
		return (0);
	if (is_wall(mapx + PLAYER_RADIUS, n_mapy, grid))
		return (0);
	if (is_wall(mapx - PLAYER_RADIUS, n_mapy, grid))
		return (0);
	return (1);
}

int	valid_x(float n_mapx, float mapy, char **grid)
{
	if (is_wall(n_mapx + PLAYER_RADIUS, mapy, grid))
		return (0);
	if (is_wall(n_mapx - PLAYER_RADIUS, mapy, grid))
		return (0);
	if (is_wall(n_mapx, mapy + PLAYER_RADIUS, grid))
		return (0);
	if (is_wall(n_mapx, mapy - PLAYER_RADIUS, grid))
		return (0);
	return (1);
}

// We validate x and y separately to allow sliding
void	valid_move(t_player *player, float x, float y, char **grid)
{
	int	n_mapx;
	int	n_mapy;

	n_mapx = player->p_x + x * SPEED;
	n_mapy = player->p_y + y * SPEED;
	if (valid_x(n_mapx, player->p_y, grid))
		player->p_x = n_mapx;
	if (valid_y(player->p_x, n_mapy, grid))
		player->p_y = n_mapy;
}
