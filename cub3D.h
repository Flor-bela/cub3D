#ifndef CUB3D_H
# define CUB3D_H

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
	t_pos		player;
}				t_data;





#endif