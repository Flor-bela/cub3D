/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:12:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/17 16:17:53 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(t_game *game)
{
	t_player	*player;
	float		fov;
	float		start_angle;
	float		step;
	int			i;

	player = &game->player;
	move_player(player, game->map.grid);
	fov = PI / 3;
	start_angle = player->p_angle - fov / 2;
	step = fov / WIDTH;
	i = 0;
	draw_background(game);
	while (i < WIDTH)
	{
		cast_ray(game, start_angle, i);
		start_angle += step;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->render.screen.img, 0, 0);
	return (0);
}
