/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:52:57 by fda-roch          #+#    #+#             */
/*   Updated: 2026/06/26 14:01:43 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_mouse(t_game *game, t_player *player)
{
	int	x;
	int	y;
	int	center_x;
	int	center_y;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	if (!game->mouse)
		return ;
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	if (x != center_x)
	{
		player->p_angle += (x - center_x) * 0.0005;
		if (player->p_angle > 2 * PI)
			player->p_angle -= 2 * PI;
		if (player->p_angle < 0)
			player->p_angle += 2 * PI;
		mlx_mouse_move(game->mlx, game->win, center_x, center_y);
		mlx_mouse_hide(game->mlx, game->win);
	}
}
