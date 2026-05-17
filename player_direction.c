/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:08:06 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/15 16:08:11 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	player_direction(t_game *game)
{
	if (game->player.pov == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
	}
	else if (game->player.pov == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
	}
	else if (game->player.pov == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
	}
	else
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
	}
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
	game->player.p_angle = atan2(game->player.dir_y, game->player.dir_x);
}
