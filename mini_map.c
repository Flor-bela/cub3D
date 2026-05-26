/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:02:15 by fda-roch          #+#    #+#             */
/*   Updated: 2026/05/26 13:47:31 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_mlx_pixel_put_minimap(t_game *game, int x, int y, int color)
{
	char	*dst;
	int		offset_x;
	int		offset_y;

	offset_x = 20;
	offset_y = 20;
	if (x + offset_x < 0 || y + offset_y < 0 || x + offset_x >= WIDTH || y + offset_y >= HEIGHT)
		return ;
	dst = game->render.screen.addr + ((y + offset_y) * game->render.screen.line_len + (x + offset_x) * (game->render.screen.bpp / 8));
	*(int *)dst = color;
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_MINI)
	{
		j = 0;
		while (j < TILE_MINI)
		{
			ft_mlx_pixel_put_minimap(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.total_row)
	{
		x = 0;
		while (x < game->map.total_column)
		{
			if (game->map.grid[y] && x < (int)ft_strlen(game->map.grid[y]))
			{
				if (game->map.grid[y][x] == '1')
					draw_square(game, x * TILE_MINI, y * TILE_MINI, 0x302D2D);
				else if (!(game->map.grid[y][x] == ' ') && !(game->map.grid[y][x] == '1'))
					draw_square(game, x * TILE_MINI, y * TILE_MINI, 0xF06262);
			}
			x++;
		}
		y++;
	}

	int player_pixel_x;
	int player_pixel_y;
	
	player_pixel_x = (int)((game->player.p_x / TILE_SIZE) * TILE_MINI) - (TILE_MINI / 2);
	player_pixel_y = (int)((game->player.p_y / TILE_SIZE) * TILE_MINI) - (TILE_MINI / 2);
	draw_square(game, player_pixel_x, player_pixel_y, 0x62D6F0);
}

void	draw_ray_on_minimap(t_game *game, float distance, float ray_angle)
{
	float	current_x;
	float	current_y;
	int		i;
	int		line_length;

	i = 0;
	line_length = (int)(distance * TILE_MINI);
	current_x = (game->player.p_x / TILE_SIZE) * TILE_MINI;
	current_y = (game->player.p_y / TILE_SIZE) * TILE_MINI;
	while (i < line_length)
	{
		ft_mlx_pixel_put_minimap(game, (int)current_x, (int)current_y, 0x00FF00);
		current_x += cos(ray_angle);
		current_y += sin(ray_angle);
		i++;
	}
}
