/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:30:39 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/20 18:27:12 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_wall(t_ray *ray, t_game *game, int i)
{
	int	color;
	int	y;

	if (ray->side == 1)
		color = 0x000000;
	else
		color = 0xFFFFFF;
	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		put_pixel(i, y, color, game);
		y++;
	}
}

void	calculate_wall(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - game->player.p_x / TILE_SIZE
				+ (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - game->player.p_y / TILE_SIZE
				+ (1 - ray->stepY) / 2) / ray->rayDirY;
	if (ray->perpWallDist < 0.0001)
		ray->perpWallDist = 0.0001;
	ray->drawStart = -(int)(HEIGHT / ray->perpWallDist) / 2 + (HEIGHT / 2);
	ray->drawEnd = (int)(HEIGHT / ray->perpWallDist) / 2 + (HEIGHT / 2);
	if (ray->drawStart < 0)
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
			ray->side = 0; // pared vertical
		}
		else
		{
			move_ray(&ray->sideDistY, ray->deltaDistY, &ray->mapY, ray->stepY);
			ray->side = 1; // pared horizontal
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
	calculate_wall(&ray, game);
	draw_wall(&ray, game, i);
	draw_ray_on_minimap(game, &ray, ray_angle);
}
