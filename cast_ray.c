/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:30:39 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/05 14:49:52 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_wall(t_ray *ray, t_game *game, int i)
{
	buffer_backwround(0, ray->drawStart, i, game);
	buffer_wall(ray, i, game);
	buffer_backwround(ray->drawEnd, HEIGHT, i, game);
}

// if ray-> side == 0 -> crosses a vertical line of the grid | -> W|E <- |
// We work only with x 
// else ->  crosses an horizontal line of the grid.  (N/S)
// We work only with y
// corrected_dist: correction of fish eye
void	calculate_wall(t_ray *ray, t_game *game, float ray_angle)
{
	float	corrected_dist;

	if (ray->side == 0)
		ray->perpWallDist = ray->sideDistX - ray->deltaDistX;
	else
		ray->perpWallDist = ray->sideDistY - ray->deltaDistY;
	corrected_dist = ray->perpWallDist
		* (cos(ray_angle - game->player.p_angle));
	if (corrected_dist < 0.1)
		corrected_dist = 0.1;
	ray->lineHeight = (int)(game->proj_plane_dist / corrected_dist);
	if (ray->lineHeight > HEIGHT * 4)
		ray->lineHeight = HEIGHT * 4;
	ray->drawStart = -(int)ray->lineHeight / 2 + (HEIGHT / 2);
	ray->drawEnd = (int)ray->lineHeight / 2 + (HEIGHT / 2);
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}

// This function checks in what direction we enter the new cell
// We check if there is a wall moving on x or y, whatever is closer
// ray->side = 0 it crosses a vertical line of the grid | -> W|E <- | (E/W)
// ray->side = 1 it crosses a horizontal line of the grid (N/S)
void	perform_dda(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	ray->side = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			move_ray(&ray->sideDistX, ray->deltaDistX, &ray->mapX, ray->stepX);
			ray->side = 0;
		}
		else
		{
			move_ray(&ray->sideDistY, ray->deltaDistY, &ray->mapY, ray->stepY);
			ray->side = 1;
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

// We need to save rays_dist in game to use it in mini_map
void	cast_ray(t_game *game, float ray_angle, int i)
{
	t_ray	ray;

	init_ray(&ray, game, ray_angle);
	perform_dda(&ray, game);
	calculate_wall(&ray, game, ray_angle);
	draw_wall(&ray, game, i);
//	debugray(ray, game, ray_angle);
	game->rays_dist[i] = ray.perpWallDist;
}
