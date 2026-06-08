/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:30:39 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/08 12:03:48 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_wall(t_ray *ray, t_game *game, int i)
{
	buffer_backwround(0, ray->draw_start, i, game);
	buffer_wall(ray, i, game);
	buffer_backwround(ray->draw_end, HEIGHT, i, game);
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
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	corrected_dist = ray->perp_wall_dist
		* (cos(ray_angle - game->player.p_angle));
	if (corrected_dist < 0.1)
		corrected_dist = 0.1;
	ray->line_height = (int)(game->proj_plane_dist / corrected_dist);
	if (ray->line_height > HEIGHT * 4)
		ray->line_height = HEIGHT * 4;
	ray->draw_start = -(int)ray->line_height / 2 + (HEIGHT / 2);
	ray->draw_end = (int)ray->line_height / 2 + (HEIGHT / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
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
		if (ray->side_dist_x < ray->side_dist_y)
		{
			move_ray(&ray->side_dist_x, ray->delta_dist_x, &ray->map_x, ray->step_x);
			ray->side = 0;
		}
		else
		{
			move_ray(&ray->side_dist_y, ray->delta_dist_y, &ray->map_y, ray->step_y);
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= game->map.total_row
			|| ray->map_x >= game->map.total_column)
		{
			ray->hit = -1;
			return ;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
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
	game->rays_dist[i] = ray.perp_wall_dist;
}
