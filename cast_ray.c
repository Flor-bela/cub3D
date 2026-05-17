/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:30:39 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/17 17:55:58 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img get_texture(t_game *game, t_ray *ray)
{
	if(ray->side == VER) // Vamos a cruzar 
	{
		if(ray->stepY == UP)
			return (game->render.textures[NO]);
		else
			return (game->render.textures[SO]);
	}
	else
	{
		if(ray->stepX == L)
			return (game->render.textures[WE]);
		else
			return (game->render.textures[EA]);
	}
}
//NO FUNCIONA :)
void	draw_wall(t_ray *ray, t_game *game, float angle, int i)
{
	int	color;
	int	y;
	int texy;
	int texx;
	t_img texture;
	float wallx;

	y = 0;
	(void)angle;
//	texture = get_texture(game, ray);
	texture = game->render.textures[NO];
	if(ray->side == VER)
		wallx = game->player.p_y + ray->perpWallDist * ray->rayDirY;
	else
		wallx = game->player.p_x + ray->perpWallDist * ray->rayDirX;
//	wallx /= 64.0;
//	printf("Wallx %f\n", wallx);
	wallx -= floor(wallx);
//	printf("Wallx %f\n", wallx);
	texx = (wallx * (32)); // las texturas que estoy usando son de 32x32
	double step = 1.0 * 32 / ray->lineHeight; // paso para completar toda la línea
	double texPos = (ray->drawStart - HEIGHT / 2 + ray->lineHeight / 2) * step; //
	while(y < ray->drawStart)
	{
		put_pixel(i, y, game->map.c_color, game);
		y++;
	}
	while(y < ray->drawEnd)
	{
		texy = (int)texPos & (32 - 1);
		texPos += step;
	//	printf("y: %d drawstart: %d lineHeight: %d texx: %d texy: %d offset: %d\n", y, ray->drawStart, ray->lineHeight, texx, texy, offset);
		color = texture.addr[32 * texy + texx];
		put_pixel(i, y, color, game);
	//	sleep(1);
		y++;
	}
	while (y < HEIGHT)
	{
		put_pixel(i, y, game->map.f_color, game);
		y++;
	}
}

void	calculate_wall(t_ray *ray, t_game *game)
{
	if (ray->side == VER)
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
			ray->side = VER; // pared vertical
		}
		else
		{
			move_ray(&ray->sideDistY, ray->deltaDistY, &ray->mapY, ray->stepY);
			ray->side = HOR; // pared horizontal
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
	draw_wall(&ray, game, ray_angle, i);
}
