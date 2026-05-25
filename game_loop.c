/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:12:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/25 16:29:40 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(t_game *game)
{
	t_player	*player;
	float		fov;
	float		start_angle;
	//float		step;
	int			i;

	player = &game->player;
	move_player(player, game->map.grid);
	fov = PI / 3;
	game->proj_plane_dist = (WIDTH / 2.0) / tan(fov / 2.0); // funcion de Danila!!!
	start_angle = player->p_angle - fov / 2;
	//step = fov / WIDTH;
	i = 0;
	draw_minimap(game);
	while (i < WIDTH)
	{
		start_angle = game->player.p_angle + atan((i - (WIDTH / 2)) / game->proj_plane_dist);
		cast_ray(game, start_angle, i);
		//start_angle += step; // no  pueden ser incrementos iguales, el angulo se ensancha cuando nos alejamos del centro!!! (si lo dejaramos con incrementos angulares fijos estaríamos proyectando el "mundo" como un cilindro)
		i++;
	}
	
	mlx_put_image_to_window(game->mlx, game->win,
		game->render.screen.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win,
		game->mini_map.img, 20, 20);
	return (0);
}
