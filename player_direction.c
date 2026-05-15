#include "cub3D.h"

void	player_direction(t_game *game)
{
	if(game->player.pov == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
	}
	else if(game->player.pov == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
	}
	else if(game->player.pov == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
	}
	else
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
	}
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
	game->player.p_angle = atan2(game->player.dir_y, game->player.dir_x);
}
