/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:02:15 by fda-roch          #+#    #+#             */
/*   Updated: 2026/05/17 17:11:42 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_mlx_pixel_put(t_game *game, int x, int y, int colour)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= (game->map.total_column * 10) || y >= (game->map.total_row * 10))
	return ;

	dst = game->mini_map.addr + (y * game->mini_map.line_len + x * (game->mini_map.bpp / 8)); // por 8 para convertirlo en bits
	*(int*)dst = colour;
}

void	draw_square(t_game *game, int x, int y, int size, int colour)
{
	int i = 0;
	int j;

	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_mlx_pixel_put(game, x + j, y + i, colour);
			j++;
		}
		i++;
	}
}
 