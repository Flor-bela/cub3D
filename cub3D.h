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
#include <string.h>

//read file
char	*fill_buffer(char *rest, int fd);
char	*read_file(char *filename);

//check file
int	ft_format(char *file);
int	correct_textures(char *map);

//error utils
void	errormsg(char *errmsg, int errnum);


#endif