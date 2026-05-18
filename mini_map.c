/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:02:15 by fda-roch          #+#    #+#             */
/*   Updated: 2026/05/18 18:43:05 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= (game->map.total_column * TILE_MINI)
		|| y >= (game->map.total_row * TILE_MINI))
		return ;
	dst = game->mini_map.addr + (y * game->mini_map.line_len + x
			* (game->mini_map.bpp / 8));
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
			ft_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_mini_map(t_game *game)
{
	int	y = 0;
	int	x;
	int	color;

	if (game->mini_map.img)
		mlx_destroy_image(game->mlx, game->mini_map.img);

	game->mini_map.img = mlx_new_image(game->mlx, game->map.total_column * TILE_MINI, game->map.total_row * TILE_MINI);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.img, &game->mini_map.bpp, &game->mini_map.line_len, &game->mini_map.endian);

	while (y < game->map.total_row)
	{
		x = 0;
		while (x < game->map.total_column)
		{
			if (!game->map.grid[y] || !game->map.grid[y][x])
			{
				while (x < game->map.total_column)
				{
					draw_square(game, x * TILE_MINI, y * TILE_MINI, 0x2C3E50);
					x++;
				}
				break ;
			}
			if (game->map.grid[y][x] == '1')
				color = 0x555555;
			else if (game->map.grid[y][x] == '0' || game->map.grid[y][x] == 'N'
				|| game->map.grid[y][x] == 'S' || game->map.grid[y][x] == 'W'
				|| game->map.grid[y][x] == 'E')
				color = 0xF5F5DC; // todo en beige
			else
				color = 0x2C3E50;
				
			draw_square(game, x * TILE_MINI, y * TILE_MINI, color);
			x++;
		}
		y++;
	}
	
	// Player
	int player_pixel_x;
	int player_pixel_y;
	player_pixel_x = (int)((game->player.p_x / TILE_SIZE) * TILE_MINI) - (TILE_MINI / 2); //tile / 2 para poder "centrar" el punto
	player_pixel_y = (int)((game->player.p_y / TILE_SIZE) * TILE_MINI) - (TILE_MINI / 2);
	draw_square(game, player_pixel_x, player_pixel_y, 0xE05A47);
}
