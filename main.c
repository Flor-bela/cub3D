/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:58:23 by medel-ca          #+#    #+#             */
/*   Updated: 2026/06/26 13:31:36 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	esc_game(int keysym, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keysym == 65307)
		close_game(game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == M)
		game->mouse = !game->mouse;
	if (keycode == N)
		game->minimap = !game->minimap;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	if (keycode == 65307)
		close_game(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;
	int		fd;

	if (ac != 2)
	{
		write(2, "Error\nUsage: ./cub3D game.cub\n", 31);
		return (1);
	}
	if (!ft_format(av[1]))
		game_destroy(NULL, "Correct format is .cub", 0);
	game = init_game();
	printf("PLAYER_RADIUS is %d\n", PLAYER_RADIUS);
	printf("BONUS is %d\n", BONUS);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		game_destroy(game, "File cannot be open", errno);
	parse_file(fd, game);
	start_game(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	game_destroy(game, NULL, 0);
	close(fd);
	return (0);
}
