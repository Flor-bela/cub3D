/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:15:08 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/25 17:39:37 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(t_player *player)
{
	if (player->left_rotate)
		player->p_angle -= A_SPEED;
	if (player->right_rotate)
		player->p_angle += A_SPEED;
	if (player->p_angle > 2 * PI)
		player->p_angle = player->p_angle - 2 * PI;
	if (player->p_angle < 0)
		player->p_angle = 2 * PI + player->p_angle;
}

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
	return (1);
}

int	valid_x(float n_mapx, float mapy, char **grid)
{
	if (is_wall(n_mapx + PLAYER_RADIUS, mapy, grid))
		return (0);
	if (is_wall(n_mapx - PLAYER_RADIUS, mapy, grid))
		return (0);
	return (1);
}

void	valid_move(t_player *player, float cos, float sin, char **grid)
{
	int	n_mapx;
	int	n_mapy;

	n_mapx = player->p_x + cos * SPEED;
	n_mapy = player->p_y + sin * SPEED;
	if (valid_x(n_mapx, player->p_y, grid))
		player->p_x = n_mapx;
	if(valid_y(player->p_x, n_mapy, grid))
		player->p_y = n_mapy;
}

void	move_player(t_player *player, char **grid)
{
	float	c_angle;
	float	s_angle;
	
	rotate_player(player);
	c_angle = cos(player->p_angle);
	s_angle = sin(player->p_angle);
	if (player->key_up)
		valid_move(player, c_angle, s_angle, grid);
	if (player->key_down)
		valid_move(player, -c_angle, -s_angle, grid);
	if (player->key_left)
		valid_move(player, s_angle, -c_angle, grid);
	if (player->key_right)
		valid_move(player, -s_angle, c_angle, grid);
}
