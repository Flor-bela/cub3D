#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>

/*
* Sructs
*/

typedef struct s_pos
{
	int			col;
	int			row;
}				t_pos;

typedef struct s_data
{
	char		**map_arr;
	int			total_rows;
	t_pos		player;
}				t_data;



// For GNL:

size_t	ft_len(const char *s);
void	ft_copy(char *dst, const char *src, size_t size);
int		free_all_gnl(char **ptr, char **result);
char	*get_next_line(int fd);



# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# if BUFFER_SIZE <=0
#  error BUFFER SIZE invalid
# endif


#endif