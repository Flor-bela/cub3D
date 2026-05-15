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
//	render_game(game); //? aquí o en el loop?
}