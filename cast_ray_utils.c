/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:06:04 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/05 14:32:45 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img	get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0) 
	{
		if (ray->step_x < 0) // | W <- |
			return (game->render.textures[WE]);
		else  // | -> E |
			return (game->render.textures[EA]);
	}
	else
	{
		if (ray->step_y < 0)
			return (game->render.textures[NO]);
		else
			return (game->render.textures[SO]);
	}
}

int	get_texx(t_player player, t_ray *ray, t_img texture)
{
	float	wallx;
	int		texx;

	if (ray->side == 0) // cruza línea en vertical del grid | -> W|E <- | (E/W) Tenemos que calcular a que altura de la pared ha caido (de 0 a n, en el eje y)
		wallx = (player.p_y / TILE_SIZE) + ray->perp_wall_dist * ray->ray_dir_y; // -> NO PUEDE DEPENDER DEL JUGADOR ???
	else // cruza línea horizontal del grid. Tenemos que calcular en que parte de la pared ha caído (de 0 a n, en el eje x)
		wallx = (player.p_x / TILE_SIZE)  + ray->perp_wall_dist * ray->ray_dir_x;
	wallx -= floor(wallx); // Nos quedamos la parte digital -> posición relativa al TILE en el que estamos
	texx = (int)(wallx * (texture.width)); // Buscamos ese punto del TILE en la textura
	if (ray->side == 0 && ray->ray_dir_x < 0) // Volteamos textura W
		texx = texture.width - texx - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0) // Volteamos textura S
		texx = texture.width - texx - 1;
	return (texx);
}

void	buffer_backwround(int start, int end, int i, t_game *game)
{
	int	y;
	int	color;

	y = start;
	if (start == 0)
		color = game->map.c_color;
	else
		color = game->map.f_color;
	while (y < end)
	{
		put_pixel(i, y, color, game);
		y++;
	}
}

void	buffer_wall(t_ray *ray, int i, t_game *game)
{
	int		color;
	t_img	texture;
	t_texcalc tex;

	texture = get_texture(game, ray);
	tex.texx = get_texx(game->player, ray, texture); // Punto variable en la textura, ejemplo: 0,0 0,1 0,2 ... tenemos que calcular la x. 
	tex.step = (double)texture.height / ray->line_height; // paso para completar toda la línea
	tex.texpos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * tex.step; // Posición en la textura al empezar a dibujar (float) Límite superior
	while (ray->draw_start < ray->draw_end)
	{
		tex.texy = (int)tex.texpos & (TILE_SIZE - 1); // Nos quedamos con la parte entera (tenemos que coger un pixel entero)
		tex.texpos += tex.step;
		if (tex.texy < 0) // Límites para no salirnos de la textura
			tex.texy = 0;
		if (tex.texy >= texture.height)
			tex.texy = texture.height - 1;
		tex.offset = (tex.texy * texture.line_len + tex.texx * (texture.bpp / 8)); // Punto en la cadena addr donde está el pixel que necesitamos
		color = *(int *)(texture.addr + tex.offset);
		put_pixel(i, ray->draw_start, color, game); // guardamos el color en el t_img screen (también está el cielo y el suelo)
		ray->draw_start++;
	}
}