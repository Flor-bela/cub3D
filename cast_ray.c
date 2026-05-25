/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:30:39 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/25 13:56:58 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	debugray(t_ray ray, t_game *game, float ray_angle)
{
	printf("player: %f %f\n", game->player.p_x, game->player.p_y);
	printf("ray hit: %d %d\n", ray.mapX, ray.mapY);
	printf("Raydir: %f %f\n", ray.rayDirX, ray.rayDirY);
	printf("Side distance: %f %f\n", ray.sideDistX, ray.sideDistY);
	printf("Delta: %f %f\n", ray.deltaDistX, ray.deltaDistY);
	printf("Step %d %d\n", ray.stepX, ray.stepY);
	printf("angle diff: %f dist: %f line: %d\n", ray_angle - game->player.p_angle, ray.perpWallDist, ray.lineHeight);
	printf("Perp wall distance: %f\n", ray.perpWallDist);
	printf("Heigh: %d, Start: %d, End: %d\n", ray.lineHeight, ray.drawStart, ray.drawEnd);
}

void	draw_wall(t_ray *ray, t_game *game, int i)
{
	buffer_backwround(0, ray->drawStart, i, game); 
	buffer_wall(ray, i, game);
	buffer_backwround(ray->drawEnd, HEIGHT, i, game);
}

void	calculate_wall(t_ray *ray, t_game *game, float ray_angle)
{
	float	corrected_dist;

	if (ray->side == 0)  // cruza línea en vertical del grid | -> W|E <- | (E/W)
		ray->perpWallDist = ray->sideDistX - ray->deltaDistX;
	else // cruza una línea en horizontal del grid (N/S)
		ray->perpWallDist = ray->sideDistY - ray->deltaDistY;
	
	corrected_dist = ray->perpWallDist * (cos(ray_angle - game->player.p_angle)); // correccion con formula de Danila para ojo de pez
	//corrected_dist = ray->perpWallDist * cos(ray_angle - ); player_angle!!!!!
	if (corrected_dist < 0.1)
		corrected_dist = 0.1;

/* 	if (ray->perpWallDist < 0.1) // Si no ajustaba el tamaño cuando la pared está muy cerca la textura era muy grande y se colgaba el programa
		ray->perpWallDist = 0.1; // Ahora se produce un "salto" en un punto cuando te alejas/acercas a una pared */

	ray->lineHeight = (int)(game->proj_plane_dist / corrected_dist);
	//ray->lineHeight = (int)(HEIGHT / (ray->perpWallDist * cos(ray_angle - game->player.p_angle)));

	if(ray->lineHeight > HEIGHT * 4) // límite para evitar paredes muy grandes
		ray->lineHeight = HEIGHT * 4;

	ray->drawStart = -(int)ray->lineHeight / 2 + (HEIGHT / 2);
	ray->drawEnd = (int)ray->lineHeight / 2 + (HEIGHT / 2);
	if (ray->drawStart < 0) // límite para evitar pintar fuera de pantalla
		ray->drawStart = 0;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}

void	perform_dda(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	ray->side = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY) // Vamos a comprobar solo si hay pared avanzando en x o y, lo que sea más corto
		{
			move_ray(&ray->sideDistX, ray->deltaDistX, &ray->mapX, ray->stepX);
			ray->side = 0; // cruza línea en vertical del grid | -> W|E <- | (E/W)
		}
		else 
		{
			move_ray(&ray->sideDistY, ray->deltaDistY, &ray->mapY, ray->stepY);
			ray->side = 1; // cruza una línea en horizontal del grid (N/S)
		}
		if (ray->mapX < 0 || ray->mapY < 0 || ray->mapY >= game->map.total_row
			|| ray->mapX >= game->map.total_column)
		{
			ray->hit = -1;
			return ;
		}
		if (game->map.grid[ray->mapY][ray->mapX] == '1')
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
	draw_ray_on_minimap(game, &ray, ray_angle);
}
