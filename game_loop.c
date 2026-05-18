/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <<fda-roch@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:12:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/18 18:37:35 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_mini_map(t_game *game)
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
					draw_square(game, x * TILE_MINI, y * TILE_MINI, TILE_MINI, 0x2C3E50);
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
				
			draw_square(game, x * TILE_MINI, y * TILE_MINI, TILE_MINI, color);
			x++;
		}
		y++;
	}
	
	int player_pixel_x;
	int player_pixel_y;
	player_pixel_x = (int)((game->player.p_x / TILE_SIZE) * TILE_MINI) - (TILE_MINI / 2); //tile / 2 para poder "centrar" el punto
	player_pixel_y = (int)((game->player.p_y / TILE_SIZE) * TILE_MINI) - (TILE_MINI / 2);
	draw_square(game, player_pixel_x, player_pixel_y, TILE_MINI, 0xE05A47);
}

int	game_loop(t_game *game)
{
	t_player	*player;
	float		fov;
	float		start_angle;
	float		step;
	int			i;

	player = &game->player;
	move_player(player, game->map.grid);
	draw_background(game);
	fov = PI / 3;
	start_angle = player->p_angle - fov / 2;
	step = fov / WIDTH;
	i = 0;
	while (i < WIDTH)
	{
		cast_ray(game, start_angle, i);
		start_angle += step;
		// mini - mapa rayos aqui?????
		i++;
	}
	init_mini_map(game);
	
	mlx_put_image_to_window(game->mlx, game->win,
		game->render.screen.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win,
		game->mini_map.img, 0, 0);
	return (0);
}
