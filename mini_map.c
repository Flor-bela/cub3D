/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:02:15 by fda-roch          #+#    #+#             */
/*   Updated: 2026/05/17 15:32:45 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int colour)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8)); // por 8 para convertirlo en bits
	*(int*)dst = colour;
}

void	draw_square(t_img *img, int x, int y, int size, int colour)
{
	int i = 0;
	int j;

	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_mlx_pixel_put(img, x + j, y + i, colour);
			j++;
		}
		i++;
	}
}
 