#include "cub3D.h"

void	debug(t_game *game)
{
	printf("NO: %s\n", game->map.text_path[NO]);
	printf("SO: %s\n", game->map.text_path[SO]);
	printf("WE: %s\n", game->map.text_path[WE]);
	printf("EA: %s\n", game->map.text_path[EA]);
	printf("Floor: %d - %d - %d\n", game->map.floor[0], game->map.floor[1], game->map.floor[2]);
	printf("Ceiling: %d - %d - %d\n", game->map.ceiling[0], game->map.ceiling[1], game->map.ceiling[2]);
	printf("Total rows: %d, Total colums: %d\n", game->map.total_row, game->map.total_column);
	printf("Posición del jugador: %f, %f, mirando hacia %c\n", game->player.p_x / TILE_SIZE, game->player.p_y / TILE_SIZE, game->player.pov);
}
