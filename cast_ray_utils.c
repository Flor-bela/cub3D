/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:06:04 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/26 12:23:06 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// step_x < 0 | W <- |
// step_x > 0 | -> E |
t_img	get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x < 0)
			return (game->render.textures[WE]);
		else
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

// if ray->side == 0 -> the ray travel in a horizontal direction,
// so it crosses a vertical line | -> W|E <- | (E/W) 
// We need to calculete the positon of the ray in the wall
// (from 0 to n, in the y axis)
// else -> the ray crosses an horizontal line in the grid. 
// We need to calculete the positon of the ray in the wall
// (from 0 to n, in the x axis)
// floor() - it returns an integer. By substracting we get the decimal part 
// -> the relative position on the TILE we are in
// texx: We need to find that point of the TILE in the texture
// S and W textures need to be mirrored
int	get_texx(t_player player, t_ray *ray, t_img texture)
{
	float	wallx;
	int		texx;

	if (ray->side == 0)
		wallx = (player.p_y / TILE_SIZE) + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wallx = (player.p_x / TILE_SIZE) + ray->perp_wall_dist * ray->ray_dir_x;
	wallx -= floor(wallx);
	texx = (int)(wallx * (texture.width));
	if (ray->side == 0 && ray->ray_dir_x < 0)
		texx = texture.width - texx - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
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

// texx: Variable point int the texture, ex.: 0,0 0,1 0,2 ...
// We need to calculate de x coordinate
// step: Increments needed to draw the whole wall
// texpos: initial position on the texture (float). Upper limit
// texy: integer (pixel)
// offset: Position inside addr where is saved the pixel we need
// put_pixel: We save that pixel in t_img screen
// (that buffer also has the ceiling and the floor colors)
void	buffer_wall(t_ray *ray, int i, t_game *game)
{
	int			color;
	t_img		texture;
	t_texcalc	tex;

	texture = get_texture(game, ray);
	tex.texx = get_texx(game->player, ray, texture);
	tex.step = (double)texture.height / ray->line_height;
	tex.texpos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* tex.step;
	while (ray->draw_start < ray->draw_end)
	{
		tex.texy = (int)tex.texpos;
		tex.texpos += tex.step;
		if (tex.texy < 0)
			tex.texy = 0;
		if (tex.texy >= texture.height)
			tex.texy = texture.height - 1;
		tex.offset = (tex.texy * texture.line_len
				+ tex.texx * (texture.bpp / 8));
		color = *(int *)(texture.addr + tex.offset);
		put_pixel(i, ray->draw_start, color, game);
		ray->draw_start++;
	}
}
