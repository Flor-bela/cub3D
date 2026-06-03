/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:12:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/03 16:50:20 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(t_game *game)
{
	t_player	*player;
	float		fov;
	float		start_angle;
	int			i;
	int			x;
	int			y;

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
	
	
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	int center_x;
	
	center_x = WIDTH / 2;
	if (x != center_x)
	{
		if (x < center_x)
			player->p_angle -= A_SPEED * 0.5; // he multiplicado para no ser tan sencible con el ratón!
		else if (x > center_x)
			player->p_angle += A_SPEED * 0.5;

		mlx_mouse_move(game->mlx, game->win, center_x, (HEIGHT / 2));
		mlx_mouse_hide(game->mlx, game->win);
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