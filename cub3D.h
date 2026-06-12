/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 14:27:13 by fda-roch          #+#    #+#             */
/*   Updated: 2026/06/12 15:36:51 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 64
# define TILE_MINI 10
//# define WIDTH 2560
//# define HEIGHT 1600
# define WIDTH 1980
# define HEIGHT 1200

# define SPEED 5
# define A_SPEED 0.05
# define PLAYER_RADIUS 10

# define W 119
# define A 97
# define S 115
# define D 100
# define M 109 // mouse
# define N 110 // minimap
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include "libft.h"
# include <string.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <stddef.h>
# include <math.h>
# include <stdbool.h>

enum e_tex
{
	NO,
	SO,
	WE,
	EA
};

typedef struct s_texcalc
{
	double	wallx;
	double	step;
	double	texpos;
	int		texx;
	int		texy;
	int		offset;
}			t_texcalc;

typedef struct s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	float	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width; //?
	int		height; //?
}			t_img;

typedef struct s_player
{
	float	p_x;
	float	p_y;
	char	pov;
	float	dir_x;
	float	dir_y;
	float	p_angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}			t_player;

typedef struct s_map
{
	char	**grid;
	int		floor[3]; // datos innecesarios?
	int		ceiling[3]; // datos innecesarios?
	int		f_color;
	int		c_color;
	char	*text_path[4];
	int		total_row;
	int		total_column;
}			t_map;

typedef struct s_render
{
	t_img	textures[4];
	t_img	screen;
}			t_render;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_render	render;
	t_map		map;
	t_player	player;
	float		proj_plane_dist;
	float		*rays_dist;
	float		*start_angle;
	bool		minimap;
	bool		mouse;
}				t_game;

//debug
void	debug(t_game *game);
void	frames_per_second(void);
void	debugray(t_ray ray, t_game *game, float ray_angle);

//init
t_game	*init_game(void);
void	free_map(t_game *game);
void	img_init(t_game *game);

//read file
char	*get_next_line(int fd);

//check file
void	close_file(int fd);
void	update_total_row(t_game *game);
int		ft_format(char *file);
int		parse_file(int fd, t_game *game);

int		extract_color(char *line, t_game *game);
int		is_color_line(char *line);
int		all_colors_found(t_game *game);

char	*extract_path(char *line);
int		extract_texture(char *line, t_game *game);
int		is_texture_line(char *line);
int		all_textures_found(t_game *game);

int		check_characters_map(t_game *game);
int		check_map_enclosed(t_game *game);

void	player_direction(t_game *game);
void	move_player(t_player *player, char **grid);

//window
void	start_game(t_game *game);
int		close_game(t_game *game);
void	game_destroy(t_game *game, char *errmsg, int errnum);
void	die(char *errmsg, int errnum);

//minimap
void	minimap(t_game *game);
void	draw_minimap(t_game *game);
void	draw_player_minimap(t_game *game);
void	draw_square(t_game *game, int x, int y, int color);
void	draw_ray_on_minimap(t_game *game, float distance, float ray_angle);
void	ft_mlx_pixel_put_minimap(t_game *game, int x, int y, int color);

//RayCast
void	cast_ray(t_game *game, float ray_angle, int i);
void	init_rayy(t_ray *ray, t_game *game, float ray_angle);
void	init_rayx(t_ray *ray, t_game *game, float ray_angle);
void	move_ray(float *sideDist, float deltaDist, int *mappos, int mapstep);
void	draw_wall(t_ray *ray, t_game *game, int i);
void	put_pixel(int x, int y, int color, t_game *game);
t_img	get_texture(t_game *game, t_ray *ray);
void	buffer_backwround(int draw_start, int draw_end, int i, t_game *game);
void	buffer_wall(t_ray *ray, int i, t_game *game);

//error utils
void	errormsg(char *errmsg, int errnum);

//utils
int		ft_isspace(char c);
char	*ft_strjoin_free(char *s1, char *s2);
int		empty_line(char *line);
int		ft_format(char *file);
void	move_mouse(t_game *game, t_player *player);
int		game_loop(t_game *game);
int		new_line(char *line);

//move player
void	valid_move(t_player *player, float x, float y, char **grid);

#endif