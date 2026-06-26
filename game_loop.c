/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:12:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/26 13:52:45 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(t_game *game)
{
	t_player	*player;
	float		fov;
	int			i;

	player = &game->player;
	move_player(player, game->map.grid);
	fov = PI / 3;
	game->proj_plane_dist = (WIDTH / 2.0) / tan(fov / 2.0);
	i = 0;
	while (i < WIDTH)
	{
		game->start_angle[i] = game->player.p_angle + atan((i - (WIDTH / 2))
				/ game->proj_plane_dist);
		cast_ray(game, game->start_angle[i], i);
		i++;
	}
	if (BONUS)
	{
		move_mouse(game, player);
		if (game->minimap == true)
			minimap(game);
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->render.screen.img, 0, 0);
	return (0);
}
