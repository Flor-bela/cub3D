/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:58:18 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/22 15:38:53 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player(t_player *player)
{
	player->p_x = 0;
	player->p_y = 0;
	player->pov = 0;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->key_up = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->map.text_path[i] = NULL;
		game->render.textures[i].img = NULL;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		game->map.ceiling[i] = -1;
		game->map.floor[i] = -1;
		i++;
	}
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		die("init_game(): malloc()", errno);
	game->mlx = NULL;
	game->win = NULL;
	game->render.screen.img = NULL;
	game->map.grid = NULL;
	game->rays_dist = (float *)malloc(sizeof(float) * WIDTH); // para el mini_mapa
	if (!game->rays_dist)
		die("init_game(): malloc()", errno);
	init_textures(game);
	game->map.total_row = 0; //necesario?
	game->map.total_column = 0; //necesario?
	init_player(&game->player);
	return (game);
}

static void	texture_load(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
	if (texture->img == 0)
		game_destroy(game, "texture_init(): can't load texture", errno);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
}

void	img_init(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		texture_load(game, &game->render.textures[i], game->map.text_path[i]);
		i++;
	}
	game->render.screen.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->render.screen.addr = mlx_get_data_addr(game->render.screen.img,
			&game->render.screen.bpp, &game->render.screen.line_len,
			&game->render.screen.endian);
}
