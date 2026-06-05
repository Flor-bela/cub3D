/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:15:08 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/05 14:30:13 by fda-roch         ###   ########.fr       */
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
	if (is_wall(n_mapx, mapy  + PLAYER_RADIUS, grid))
		return (0);
	if (is_wall(n_mapx, mapy  - PLAYER_RADIUS, grid))
		return (0);
	return (1);
}

void	valid_move(t_player *player, float x, float y, char **grid)
{
	int	n_mapx;
	int	n_mapy;

	n_mapx = player->p_x + x * SPEED;
	n_mapy = player->p_y + y * SPEED;
	
	if (valid_x(n_mapx, player->p_y, grid))  //Validar x e y por separado para que deslice por las paredes
		player->p_x = n_mapx;
	if(valid_y(player->p_x, n_mapy, grid))
		player->p_y = n_mapy;
}

void	move_player(t_player *player, char **grid)
{
	float forward_x;
	float forward_y;
	float right_x;
	float right_y;
	int	forward;
	int strafe;
	float move_x;
	float move_y;
	float length;

	rotate_player(player);
	forward_x = cos(player->p_angle); //Vector de intención UP/DOWN
	forward_y = sin(player->p_angle); 
	right_x = sin(player->p_angle); //Vector de intención LEFT/RIGHT
	right_y = -cos(player->p_angle);
	forward = player->key_up - player->key_down; //Signo del movimiento según la tecla
	strafe = player->key_left - player->key_right;
	move_x = forward_x * forward + right_x * strafe; //Convinación de las dos intenciones
	move_y = forward_y * forward + right_y * strafe;
	length = sqrt(move_x * move_x + move_y * move_y); // Longitud del vector de dirección (formula hipotenusa)
	if (length > 1) //Normalizar a 1 para que no se mueva más rápido en diagonal
	{
		move_x /= length;
		move_y /= length;
	}
	valid_move(player, move_x, move_y, grid); // Actualizar la posición si el movimiento es válido
}

