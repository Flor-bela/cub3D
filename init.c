/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:58:18 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/17 15:36:19 by fda-roch         ###   ########.fr       */
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
/* 
static void	init_mini_map(t_game *game)
{
	int		y = 0; // rows
	int		x; // cols
	int		tile = 10; // Tamaño de cada cuadro en el minimapa
	int		colour;

	game->mini_map.img = mlx_new_image(game->mlx, game->map.total_column * tile, game->map.total_row * tile);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.img, &game->mini_map.bpp, &game->mini_map.line_len, &game->mini_map.endian);

	while (y < game->map.total_row)
	{
		x = 0;
		while (x < game->map.total_column)
		{
			if (game->map.grid[y][x] == '1')
				colour = 0x000000;
			else if (game->map.grid[y][x] == '0')
				colour = 0xFFFFFF; 
			else if (game->map.grid[y][x] == 'N' || game->map.grid[y][x] == 'S' || game->map.grid[y][x] == 'W' || game->map.grid[y][x] == 'E')
				colour = 0x00FF00; // verde
			else
				colour = 0x808080; // gris?? para los espacios sin nada
			draw_square(game->mini_map.img, x * tile, y * tile, tile, colour);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 20, 20); //en el rincón izquierdo
	//destroy image at the end too!!!
} */

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
	//init_mini_map(game);
	init_textures(game);
	game->map.total_row = 0; //necesario?
	game->map.total_column = 0; //necesario?
	init_player(&game->player);
	return (game);
}

static void	texture_load(t_game *game, t_img *texture, char *path)
{
	int	len;

	len = TILE_SIZE;
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &len, &len);
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

