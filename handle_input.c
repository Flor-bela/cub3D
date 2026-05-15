#include "cub3D.h"

void put_pixel(int x, int y, int color, t_game *game)
{
	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	int index = y * game->render.screen.line_len + x * game->render.screen.bpp / 8;
	*(unsigned int *)(game->render.screen.addr + index) = color;
}

void draw_background(t_game *game)
{
    int x, y;
    int *buf = (int *)game->render.screen.addr;
    int line = game->render.screen.line_len / 4;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            if (y < HEIGHT / 2)
                buf[y * line + x] = game->map.c_color;
            else
                buf[y * line + x] = game->map.f_color;
            x++;
        }
        y++;
    }
}

void	move_player(t_player *player)
{
	int speed = 10;
	float angle_speed = 0.5;

	if(player->left_rotate)
		player->p_angle -= angle_speed;
	if(player->right_rotate)
		player->p_angle +=angle_speed;
	if(player->p_angle > 2 * PI)
		player->p_angle = 0;
	if(player->p_angle < 0)
	 	player->p_angle = 2 * PI;
	float cos_angle = cos(player->p_angle);
	float sin_angle = sin(player->p_angle);

	
	if(player->key_up)
	{
		player->p_x += cos_angle * speed;
		player->p_y += sin_angle * speed;
	}
	if(player->key_down)
	{
		player->p_x -= cos_angle * speed;
		player->p_y -= sin_angle * speed;
	}
	if(player->key_left)
	{
		player->p_x += sin_angle * speed;
		player->p_y -= cos_angle * speed;
	}
	if(player->key_right)
	{
		player->p_x -= sin_angle * speed;
		player->p_y += cos_angle * speed;
	}
}

void	init_ray(t_ray *ray, t_game *game, float ray_angle)
{
	ray->rayDirX = cos(ray_angle); // vector de dirección según el ángulo del jugador
	ray->rayDirY = sin(ray_angle);
	ray->mapX = game->player.p_x / TILE_SIZE; // de posición real a casillas de mapa
	ray->mapY = game->player.p_y / TILE_SIZE;
	if (ray->rayDirX == 0)  // distancia hacia linea vertical
    	ray->deltaDistX = 1e30; // Si la dirección del jugador es vertical no va a atravesar lineas verticales
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX); // fabs: valor absoluto

	if (ray->rayDirY == 0)  // distancia hacia linea horizontal
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	if (ray->rayDirX < 0) // dirección del salto
		ray->stepX = -1; // Izquierda
	else
		ray->stepX = 1; // Derecha
	if (ray->rayDirY < 0)
		ray->stepY = -1; // Arriba
	else
		ray->stepY = 1; // Abajo
	if (ray->rayDirX < 0)  // Distancia hasta la primera linea vertical
	{
		ray->sideDistX =
			(game->player.p_x / TILE_SIZE - ray->mapX)
			* ray->deltaDistX;
	}
	else
	{
		ray->sideDistX =
			(ray->mapX + 1.0 - game->player.p_x / TILE_SIZE)
			* ray->deltaDistX;
	}
	if (ray->rayDirY < 0) // Distancia hasta la primera linea horizontal
	{
		ray->sideDistY =
			(game->player.p_y / TILE_SIZE - ray->mapY)
			* ray->deltaDistY;
	}
	else
	{
		ray->sideDistY =
			(ray->mapY + 1.0 - game->player.p_y / TILE_SIZE)
			* ray->deltaDistY;
	}
}
void	draw_wall(t_ray *ray, t_game *game, int i)
{
	int color;

	if (ray->side == 1)
		color = 0xAAAAAA; // más oscuro
	else
		color = 0xFFFFFF;
	int y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		put_pixel(i, y, color, game);
		y++;
	}
}
void	calculate_wall(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	ray->perpWallDist = (ray->mapX - game->player.p_x / TILE_SIZE
    	+ (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - game->player.p_y / TILE_SIZE
    	+ (1 - ray->stepY) / 2) / ray->rayDirY;
	if (ray->perpWallDist < 0.0001)
    	ray->perpWallDist = 0.0001;
	ray->drawStart = -(int)(HEIGHT / ray->perpWallDist) / 2 + (HEIGHT / 2);
	ray->drawEnd = (int)(HEIGHT / ray->perpWallDist) / 2 + (HEIGHT / 2);
	if (ray->drawStart < 0)
   		ray->drawStart = 0;
	if (ray->drawEnd >= HEIGHT)
    	ray->drawEnd = HEIGHT - 1;
}

void	perform_dda(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	ray->side = 0;

	while(ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->mapX < 0 || ray->mapY < 0 || ray->mapY >= game->map.total_column 
			|| ray->mapX >= game->map.total_row)
		{
			ray->hit = 1;
			return;
		}
		if (game->map.grid[ray->mapY][ray->mapX] == '1')
    		ray->hit = 1;
	}
}

void	cast_ray(t_game *game, float ray_angle, int i)
{
	t_ray ray;

    init_ray(&ray, game, ray_angle);
    perform_dda(&ray, game);
    calculate_wall(&ray, game);
	draw_wall(&ray, game, i);
}

int	game_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	draw_background(game);
	float fov = PI / 3;

	float start_angle = player->p_angle - fov / 2;
	float step = fov / WIDTH;
	int i = 0;
	while(i < WIDTH)
	{
		cast_ray(game, start_angle, i);
		start_angle += step;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->render.screen.img, 0, 0);
	return (0);
}
