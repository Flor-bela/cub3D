#include "cub3D.h"

t_img	get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0) 
	{
		if (ray->stepX < 0) // | W <- |
			return (game->render.textures[WE]);
		else  // | -> E |
			return (game->render.textures[EA]);
	}
	else
	{
		if (ray->stepY < 0)
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
		wallx = player.p_y + ray->perpWallDist * ray->rayDirY;
	else // cruza línea horizontal del grid. Tenemos que calcular en que parte de la pared ha caído (de 0 a n, en el eje x)
		wallx = player.p_x + ray->perpWallDist * ray->rayDirX; 
	wallx -= floor(wallx); // Nos quedamos la parte digital -> posición relativa al TILE en el que estamos
	texx = (int)(wallx * (texture.width)); // Buscamos ese punto del TILE en la textura
	if (ray->side == 0 && ray->stepX < 0) // Volteamos textura W
		texx = texture.width - texx - 1;
	if (ray->side == 1 && ray->stepY > 0) // Volteamos textura S
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
	int		y;
	int		color;
	t_img	texture;
	t_texcalc tex;

	texture = get_texture(game, ray);
	tex.texx = get_texx(game->player, ray, texture); // Punto variable en la textura, ejemplo: 0,0 0,1 0,2 ... tenemos que calcular la x. 
	tex.step = (double)texture.height / ray->lineHeight; // paso para completar toda la línea
	tex.texpos = 0; // Posición en la textura al empezar a dibujar (float) Límite superior
	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		tex.texy = (int)tex.texpos; // Nos quedamos con la parte entera (tenemos que coger un pixel entero)
		if (tex.texy < 0) // Límites para no salirnos de la textura
			tex.texy = 0;
		if (tex.texy >= texture.height)
			tex.texy = texture.height - 1;
		tex.offset = (tex.texy * texture.line_len + tex.texx * (texture.bpp / 8)); // Punto en la cadena addr donde está el pixel que necesitamos
		color = *(int *)(texture.addr + tex.offset);
		put_pixel(i, y, color, game); // guardamos el color en el t_img screen (también está el cielo y el suelo)
		tex.texpos += tex.step;
		y++;
	}
}
