/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:12:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/26 17:24:53 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(t_game *game)
{
	t_player	*player;
	float		fov;
	float		start_angle;
	int			i;

	player = &game->player;
	move_player(player, game->map.grid);
	fov = PI / 3;
	game->proj_plane_dist = (WIDTH / 2.0) / tan(fov / 2.0); // funcion de Danila!!!
	i = 0;
	while (i < WIDTH)
	{
		start_angle = game->player.p_angle + atan((i - (WIDTH / 2)) / game->proj_plane_dist);
		cast_ray(game, start_angle, i);
		//start_angle += step; // no  pueden ser incrementos iguales, el angulo se ensancha cuando nos alejamos del centro!!! (si lo dejaramos con incrementos angulares fijos estaríamos proyectando el "mundo" como un cilindro)
		i++;
	}
	draw_minimap(game);
	i = 0;
	while (i < WIDTH)
	{
		start_angle = game->player.p_angle + atan((i - (WIDTH / 2)) / game->proj_plane_dist);
		draw_ray_on_minimap(game, game->rays_dist[i], start_angle);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->render.screen.img, 0, 0);
	return (0);
}
