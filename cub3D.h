#ifndef CUB3D_H
# define CUB3D_H
# define TILE_LEN  32

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include "libft.h"
# include <string.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <mlx.h>

typedef struct s_img
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
}	t_img;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textures;

typedef struct s_colors
{
	int	floor[3];
	int	ceiling[3];
}	t_colors;

typedef struct s_pos
{
	int			col;
	int			row;
}				t_pos;

typedef struct s_map
{
	t_textures	textures;
	t_colors	colors;
	char		**grid;
	int			total_rows;
	t_pos		player;
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	t_img	*img;
}	t_map;

//debug
void	debug(t_map *map);

//init
t_map	*init_map(void);
void	destroy_map(t_map *map);

//read file
char	*get_next_line(int fd);

//check file
int		ft_format(char *file);
int		parse_file(int fd, t_map *map);

int		extract_color(char *line, t_map *map);
int		is_color_line(char *line);
int		all_colors_found(t_map *map);

char	*extract_path(char *line);
int	 	extract_texture(char *line, t_map *map);
int		is_texture_line(char *line);
int		all_textures_found(t_map *map);

int		check_characters_map(t_map *map);
int		check_map_enclosed(t_map *map);


//error utils
void	errormsg(char *errmsg, int errnum);

//utils
int		ft_isspace(char c);
char	*ft_strcpy(char *str, int size);
char	*ft_strjoin_free(char *s1, char *s2);
int		empty_line(char *line);
int		ft_format(char *file);

#endif