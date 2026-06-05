/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:12:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/05 13:54:00 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_mouse(t_game *game, t_player *player)
{
	int	new_x;
	int	new_y;
	
	mlx_mouse_get_pos(game->mlx, game->win, &new_x, &new_y);
	if (game->x != new_x && new_x >= 0 && new_x <= WIDTH && new_y >= 0 && new_y <= HEIGHT)
	{
		if (new_x < game->x)
			player->p_angle -= A_SPEED * 0.5;
		else if (new_x > game->x)
			player->p_angle += A_SPEED * 0.5;
		game->x = new_x;
	}
}

static void	minimap(t_game *game)
{
	int		i;
	float	start_angle;

	i = 0;
	draw_minimap(game);
	while (i < WIDTH)
	{
		start_angle = game->player.p_angle + atan((i - (WIDTH / 2)) / game->proj_plane_dist);
		draw_ray_on_minimap(game, game->rays_dist[i], start_angle);
		i++;
	}
}
	
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
		i++;
	}
	frames_per_second();
	move_mouse(game, player);
	if (game->minimap == true)
		minimap(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->render.screen.img, 0, 0);
	return (0);
}
