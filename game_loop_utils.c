/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:16:48 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/05 14:57:40 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// index: We jump all the necessary rows (y)
// until the current column (x)
// We save the new color in the corresponding position on the string
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->render.screen.line_len + x * game->render.screen.bpp / 8;
	*(unsigned int *)(game->render.screen.addr + index) = color;
}

void	move_ray(float *sideDist, float deltaDist, int *mappos, int mapstep)
{
	*sideDist += deltaDist;
	*mappos += mapstep;
}

// Horizontal axis -> distance between vertical lines
// rayDirX: direction vector based on the player angle
// mapX: cell in the map, acording to the real position
// if rayDiX == 0 (vertical dir) We are not crossing cells, huge delta
// fabs(): absolute value
// ray->DirX < 0 we move to the left (W)
// ray->DirX > 0 we move to the right (E)
void	init_rayx(t_ray *ray, t_game *game, float ray_angle)
{
	ray->rayDirX = cos(ray_angle);
	ray->mapX = game->player.p_x / TILE_SIZE;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirX < 0)
	{
		ray->sideDistX = (game->player.p_x / TILE_SIZE - ray->mapX)
			* ray->deltaDistX;
		ray->stepX = -1;
	}
	else
	{
		ray->sideDistX = (ray->mapX + 1.0 - game->player.p_x / TILE_SIZE)
			* ray->deltaDistX;
		ray->stepX = 1;
	}
}

// Vertical axis -> distance between horizontal lines
// if ray->rayDirY < 0 we move up (N)
// ray->rayDirY > 0 we move down (S)
void	init_rayy(t_ray *ray, t_game *game, float ray_angle)
{
	ray->rayDirY = sin(ray_angle);
	ray->mapY = game->player.p_y / TILE_SIZE;
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player.p_y / TILE_SIZE - ray->mapY)
			* ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->player.p_y / TILE_SIZE)
			* ray->deltaDistY;
	}
}
