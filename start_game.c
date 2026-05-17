/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:08:37 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/15 16:08:47 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	start_game(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		game_destroy(game, "Fail to init mlx", errno);
	game->win = mlx_new_window(game->mlx, WIDTH,
			HEIGHT, "Not Doom");
	if (game->win == NULL)
		game_destroy(game, "Fail to create new window", errno);
	img_init(game);
}
