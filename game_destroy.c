/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:53:35 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/09 13:19:05 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	free(game->map.text_path[NO]);
	free(game->map.text_path[SO]);
	free(game->map.text_path[WE]);
	free(game->map.text_path[EA]);
	if (game->map.grid)
	{
		while (game->map.grid[i])
		{
			free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
}

static void	game_destroy_images(t_game *game)
{
	int	i;

	if (!game || !game->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->render.textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->render.textures[i].img);
			game->render.textures[i].img = NULL;
		}
		i++;
	}
	mlx_destroy_image(game->mlx, game->render.screen.img);
}

void	game_destroy(t_game *game, char *errmsg, int errnum)
{
	if (game)
	{
		game_destroy_images(game);
		if (game->mlx)
		{
			if (game->win)
				mlx_destroy_window(game->mlx, game->win);
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		free(game->rays_dist);
		free(game->start_angle);
		free_map(game);
		free(game);
	}
	die(errmsg, errnum);
}

void	die(char *errmsg, int errnum)
{
	if (errmsg != 0 || errnum != 0)
		ft_putendl_fd("Error", 2);
	if (errmsg != 0)
		ft_putstr_fd(errmsg, 2);
	if (errmsg != 0 && errnum != 0)
		ft_putstr_fd(": ", 2);
	if (errnum != 0)
		ft_putstr_fd(strerror(errnum), 2);
	if (errmsg != 0 || errnum != 0)
	{
		ft_putendl_fd("", 2);
		exit(1);
	}
	if (errmsg == 0) // para minimap
		exit(1);
	exit(0);
}

int	close_game(t_game *game)
{
	ft_putendl_fd("¡Gracias por jugar!", 1);
	game_destroy(game, NULL, 0);
	exit (0);
}
