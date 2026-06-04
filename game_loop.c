/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:12:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/04 18:13:04 by fda-roch         ###   ########.fr       */
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
			player->p_angle -= A_SPEED * 0.5; // he multiplicado para no ser tan sencible con el ratón!
		else if (new_x > game->x)
			player->p_angle += A_SPEED * 0.5;
		game->x = new_x;
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
		//start_angle += step; // no  pueden ser incrementos iguales, el angulo se ensancha cuando nos alejamos del centro!!! (si lo dejaramos con incrementos angulares fijos estaríamos proyectando el "mundo" como un cilindro)
		i++;
	}

	//
	static struct timeval	old_time;
	static struct timeval	current_time;
	static int				initialized = 0;

	if (initialized == 0)
	{	
		gettimeofday(&old_time, NULL);
		initialized = 1;
	}
	gettimeofday(&current_time, NULL);
	long	delta_seconds;
	long	delta_useconds;
	double	delta_time;
	double	fps;
	
	delta_seconds = current_time.tv_sec - old_time.tv_sec;
	delta_useconds = current_time.tv_usec - old_time.tv_usec;
	delta_time = (double)delta_seconds + (double)(delta_useconds / 1000000.0);
	fps = 1.0 / delta_time;
	printf("FPS: %.2f\n", fps);

	old_time.tv_sec = current_time.tv_sec;
	old_time.tv_usec = current_time.tv_usec;
	//

	
	move_mouse(game, player);
	//
	draw_minimap(game);
	i = 0;
	while (i < WIDTH)
	{
		start_angle = game->player.p_angle + atan((i - (WIDTH / 2)) / game->proj_plane_dist);
		draw_ray_on_minimap(game, game->rays_dist[i], start_angle);
		i++;
	}
	//
	mlx_put_image_to_window(game->mlx, game->win,
		game->render.screen.img, 0, 0);
	return (0);
}
