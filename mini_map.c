#include "cub3D.h"

void	mini_game(t_game *game)
{
	int	y;
	int	x;
	char *dst;

	y = 0;
	
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			my_mlx_pixel_put(game->screen, x, y, game->colors.c_color);
			x++;
		}
		y++;
	}
}