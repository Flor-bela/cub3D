/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:16:48 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/20 16:30:25 by medel-ca         ###   ########.fr       */
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
	ray->rayDirX = cos(ray_angle); // vector de dirección según el ángulo del jugador 
	ray->mapX = game->player.p_x / TILE_SIZE; // de posición real a casillas de mapa
	if (ray->rayDirX == 0) // distancia hacia linea vertical
		ray->deltaDistX = 1e30; // Si la dirección del jugador es vertical no va a atravesar lineas verticales
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX); // fabs: valor absoluto
	if (ray->rayDirX < 0) // Distancia hasta la primera linea vertical (hacia izda.)
	{
		ray->sideDistX = (game->player.p_x / TILE_SIZE - ray->mapX)
			* ray->deltaDistX;
		ray->stepX = -1; // Izquierda (W)
	}
	else // hacia dcha.
	{
		ray->sideDistX = (ray->mapX + 1.0 - game->player.p_x / TILE_SIZE)
			* ray->deltaDistX;
		ray->stepX = 1; // Derecha (E)
	}
}

void	init_rayy(t_ray *ray, t_game *game, float ray_angle)
{
	ray->rayDirY = sin(ray_angle);
	ray->mapY = game->player.p_y / TILE_SIZE;
	if (ray->rayDirY == 0) // distancia hacia linea horizontal
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	if (ray->rayDirY < 0) // Distancia hasta la primera linea horizontal (hacia arriba)
	{
		ray->stepY = -1; // Arriba (N)
		ray->sideDistY = (game->player.p_y / TILE_SIZE - ray->mapY)
			* ray->deltaDistY;
	}
	else //hacia abajo
	{
		ray->stepY = 1; // Abajo (S)
		ray->sideDistY = (ray->mapY + 1.0 - game->player.p_y / TILE_SIZE)
			* ray->deltaDistY;
	}
}
