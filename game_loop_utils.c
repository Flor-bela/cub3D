/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:16:48 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/08 12:03:48 by fda-roch         ###   ########.fr       */
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
// ray_dir_x: direction vector based on the player angle
// map_x: cell in the map, acording to the real position
// if rayDiX == 0 (vertical dir) We are not crossing cells, huge delta
// fabs(): absolute value
// ray->DirX < 0 we move to the left (W)
// ray->DirX > 0 we move to the right (E)
void	init_rayx(t_ray *ray, t_game *game, float ray_angle)
{
	ray->ray_dir_x = cos(ray_angle);
	ray->map_x = game->player.p_x / TILE_SIZE;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_x < 0)
	{
		ray->side_dist_x = (game->player.p_x / TILE_SIZE - ray->map_x)
			* ray->delta_dist_x;
		ray->step_x = -1;
	}
	else
	{
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.p_x / TILE_SIZE)
			* ray->delta_dist_x;
		ray->step_x = 1;
	}
}

// Vertical axis -> distance between horizontal lines
// if ray->ray_dir_y < 0 we move up (N)
// ray->ray_dir_y > 0 we move down (S)
void	init_rayy(t_ray *ray, t_game *game, float ray_angle)
{
	ray->ray_dir_y = sin(ray_angle);
	ray->map_y = game->player.p_y / TILE_SIZE;
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.p_y / TILE_SIZE - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.p_y / TILE_SIZE)
			* ray->delta_dist_y;
	}
}
