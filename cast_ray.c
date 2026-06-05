/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:30:39 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/05 14:32:45 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	debugray(t_ray ray, t_game *game, float ray_angle)
{
	printf("player: %f %f\n", game->player.p_x, game->player.p_y);
	printf("ray hit: %d %d\n", ray.mapx, ray.mapy);
	printf("Raydir: %f %f\n", ray.ray_dir_x, ray.ray_dir_y);
	printf("Side distance: %f %f\n", ray.side_dist_x, ray.side_dist_y);
	printf("Delta: %f %f\n", ray.delta_dist_x, ray.delta_dist_y);
	printf("Step %d %d\n", ray.step_x, ray.step_y);
	printf("angle diff: %f dist: %f line: %d\n", ray_angle - game->player.p_angle, ray.perp_wall_dist, ray.line_height);
	printf("Perp wall distance: %f\n", ray.perp_wall_dist);
	printf("Heigh: %d, Start: %d, End: %d\n", ray.line_height, ray.draw_start, ray.draw_end);
}

void	draw_wall(t_ray *ray, t_game *game, int i)
{
	buffer_backwround(0, ray->draw_start, i, game); 
	buffer_wall(ray, i, game);
	buffer_backwround(ray->draw_end, HEIGHT, i, game);
}

void	calculate_wall(t_ray *ray, t_game *game, float ray_angle)
{
	float	corrected_dist;

	if (ray->side == 0)  // cruza línea en vertical del grid | -> W|E <- | (E/W)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else // cruza una línea en horizontal del grid (N/S)
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	
	corrected_dist = ray->perp_wall_dist * (cos(ray_angle - game->player.p_angle)); // correccion con formula de Danila para ojo de pez
	//corrected_dist = ray->perp_wall_dist * cos(ray_angle - ); player_angle!!!!!
	if (corrected_dist < 0.1)
		corrected_dist = 0.1;

/* 	if (ray->perp_wall_dist < 0.1) // Si no ajustaba el tamaño cuando la pared está muy cerca la textura era muy grande y se colgaba el programa
		ray->perp_wall_dist = 0.1; // Ahora se produce un "salto" en un punto cuando te alejas/acercas a una pared */

	ray->line_height = (int)(game->proj_plane_dist / corrected_dist);
	//ray->line_height = (int)(HEIGHT / (ray->perp_wall_dist * cos(ray_angle - game->player.p_angle)));

	if(ray->line_height > HEIGHT * 4) // límite para evitar paredes muy grandes
		ray->line_height = HEIGHT * 4;

	ray->draw_start = -(int)ray->line_height / 2 + (HEIGHT / 2);
	ray->draw_end = (int)ray->line_height / 2 + (HEIGHT / 2);
	if (ray->draw_start < 0) // límite para evitar pintar fuera de pantalla
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	perform_dda(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	ray->side = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y) // Vamos a comprobar solo si hay pared avanzando en x o y, lo que sea más corto
		{
			move_ray(&ray->side_dist_x, ray->delta_dist_x, &ray->mapx, ray->step_x);
			ray->side = 0; // cruza línea en vertical del grid | -> W|E <- | (E/W)
		}
		else 
		{
			move_ray(&ray->side_dist_y, ray->delta_dist_y, &ray->mapy, ray->step_y);
			ray->side = 1; // cruza una línea en horizontal del grid (N/S)
		}
		if (ray->mapx < 0 || ray->mapy < 0 || ray->mapy >= game->map.total_row
			|| ray->mapx >= game->map.total_column)
		{
			ray->hit = -1;
			return ;
		}
		if (game->map.grid[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
}

void	init_ray(t_ray *ray, t_game *game, float ray_angle)
{
	init_rayx(ray, game, ray_angle);
	init_rayy(ray, game, ray_angle);
}

void	cast_ray(t_game *game, float ray_angle, int i)
{
	t_ray	ray;
	
	init_ray(&ray, game, ray_angle);
	perform_dda(&ray, game);
	calculate_wall(&ray, game, ray_angle);
	draw_wall(&ray, game, i);
//	debugray(ray, game, ray_angle);
	game->rays_dist[i] = ray.perp_wall_dist; // guardarlo aquí para no volver a calcularlo para el mini_mapa
}
