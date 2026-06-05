/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:16:48 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/05 14:31:31 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->render.screen.line_len + x * game->render.screen.bpp / 8; // Avanzamos las filas necesarias (y) hasta llegar a la columna actual (x)
	*(unsigned int *)(game->render.screen.addr + index) = color; // Guardamos el nuevo color en la posición correspondiente del string
}

void	move_ray(float *sideDist, float deltaDist, int *mappos, int mapstep)
{
	*sideDist += deltaDist;
	*mappos += mapstep;
}

// Eje horizontal -> calcula las distancias entre las líneas verticales
void	init_rayx(t_ray *ray, t_game *game, float ray_angle)
{
	ray->ray_dir_x = cos(ray_angle); // vector de dirección según el ángulo del jugador 
	ray->mapx = game->player.p_x / TILE_SIZE; // de posición real a casillas de mapa
	if (ray->ray_dir_x == 0) // distancia hacia linea vertical
		ray->delta_dist_x = 1e30; // Si la dirección del jugador es vertical no va a atravesar lineas verticales
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x); // fabs: valor absoluto
	if (ray->ray_dir_x < 0) // Distancia hasta la primera linea vertical (hacia izda.)
	{
		ray->side_dist_x = (game->player.p_x / TILE_SIZE - ray->mapx)
			* ray->delta_dist_x;
		ray->step_x = -1; // Izquierda (W)
	}
	else // hacia dcha.
	{
		ray->side_dist_x = (ray->mapx + 1.0 - game->player.p_x / TILE_SIZE)
			* ray->delta_dist_x;
		ray->step_x = 1; // Derecha (E)
	}
}

void	init_rayy(t_ray *ray, t_game *game, float ray_angle)
{
	ray->ray_dir_y = sin(ray_angle);
	ray->mapy = game->player.p_y / TILE_SIZE;
	if (ray->ray_dir_y == 0) // distancia hacia linea horizontal
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_y < 0) // Distancia hasta la primera linea horizontal (hacia arriba)
	{
		ray->step_y = -1; // Arriba (N)
		ray->side_dist_y = (game->player.p_y / TILE_SIZE - ray->mapy)
			* ray->delta_dist_y;
	}
	else //hacia abajo
	{
		ray->step_y = 1; // Abajo (S)
		ray->side_dist_y = (ray->mapy + 1.0 - game->player.p_y / TILE_SIZE)
			* ray->delta_dist_y;
	}
}
