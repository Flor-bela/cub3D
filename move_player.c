/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:15:08 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/05 15:00:24 by medel-ca         ###   ########.fr       */
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

// forward_ = Intention vector UP/DOWN
// rigth_ = Intention vector LEFT/RIGHT
// forward/ strafe: Moving sign acording to the pressed key
// move_: convination of the 2 intentions
// length: length of the direction vector (hipotenuse formula)
// if > 1 -> normalice to 1 so it does not move faster in the diagonals
float	calculate_vector_y(t_player *player)
{
	float	forward_y;
	float	right_y;
	int		forward;
	int		strafe;
	float	move_y;

	forward_y = sin(player->p_angle);
	right_y = -cos(player->p_angle);
	forward = player->key_up - player->key_down;
	strafe = player->key_left - player->key_right;
	move_y = forward_y * forward + right_y * strafe;
	return (move_y);
}

float	calculate_vector_x(t_player *player)
{
	float	forward_x;
	float	right_x;
	int		forward;
	int		strafe;
	float	move_x;

	forward_x = cos(player->p_angle);
	right_x = sin(player->p_angle);
	forward = player->key_up - player->key_down;
	strafe = player->key_left - player->key_right;
	move_x = forward_x * forward + right_x * strafe;
	return (move_x);
}

void	move_player(t_player *player, char **grid)
{
	float	move_x;
	float	move_y;
	float	length;

	rotate_player(player);
	move_x = calculate_vector_x(player);
	move_y = calculate_vector_y(player);
	length = sqrt(move_x * move_x + move_y * move_y);
	if (length > 1)
	{
		move_x /= length;
		move_y /= length;
	}
	valid_move(player, move_x, move_y, grid);
}
