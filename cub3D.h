#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include "libft.h"
# include <string.h>

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

typedef struct s_map
{
	t_textures	textures;
	t_colors	colors;
//	char		**grid;
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

int		parse_color(char *line, t_map *map);
int		is_color_line(char *line);

char	*extract_path(char *line);
int		parse_texture(char *line, t_map *map);
int		is_texture_line(char *line);

//error utils
void	errormsg(char *errmsg, int errnum);

//utils
int		ft_isspace(char c);
char	*ft_strcpy(char *str, int size);

#endif