/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:52:05 by fda-roch          #+#    #+#             */
/*   Updated: 2026/06/26 14:01:38 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	minimap(t_game *game)
{
	int	i;

	i = 0;
	draw_minimap(game);
	while (i < WIDTH)
	{
		draw_ray_on_minimap(game, game->rays_dist[i], game->start_angle[i]);
		i++;
	}
}
