/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:02:15 by fda-roch          #+#    #+#             */
/*   Updated: 2026/05/18 18:36:50 by fda-roch         ###   ########.fr       */
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

void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
