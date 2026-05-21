/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:15:08 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/21 10:03:38 by medel-ca         ###   ########.fr       */
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

void	move(t_player *player, float cos, float sin)
{
	player->p_x += cos * SPEED;
	player->p_y += sin * SPEED;
}

int	valid_move(t_player player, float cos, float sin, char **grid)
{
	int	n_mapx;
	int	n_mapy;
	int mapx;
	int mapy;

	mapx = player.p_x / TILE_SIZE;
	mapy = player.p_y / TILE_SIZE;
	n_mapx = (player.p_x + cos * SPEED) / TILE_SIZE;
	n_mapy = (player.p_y + sin * SPEED) / TILE_SIZE;	
	if (grid[mapy][n_mapx] == '1')
		return (0);	
	if (grid[n_mapy][mapx] == '1')
		return (0);
	if (grid[n_mapy][n_mapx] == '1')
		return (0);
	return (1);
}

void	move_player(t_player *player, char **grid)
{
	float	c_angle;
	float	s_angle;
	
	rotate_player(player);
	c_angle = cos(player->p_angle);
	s_angle = sin(player->p_angle);
	if (player->key_up && valid_move(*player, c_angle, s_angle, grid))
		move(player, c_angle, s_angle);
	if (player->key_down && valid_move(*player, -c_angle, -s_angle, grid))
		move(player, -c_angle, -s_angle);
	if (player->key_left && valid_move(*player, s_angle, -c_angle, grid))
		move(player, s_angle, -c_angle);
	if (player->key_right && valid_move(*player, -s_angle, c_angle, grid))
		move(player, -s_angle, c_angle);
}
