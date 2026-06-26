/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:12:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/26 13:31:02 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	minimap(t_game *game)
{
	int	i;

	i = 0;
	draw_minimap(game);
	while (i < WIDTH)
	{
		draw_ray_on_minimap(game, game->rays_dist[i], game->start_angle[i]);
		i++;
	}
}

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
