#include "cub3D.h"

int	ft_format(char *file)
{
	size_t	len;

	len = ft_strlen(file) - 1;
	if(file[len] == 'b' && file[len - 1] == 'u'
		&& file[len - 2] == 'c' && file[len - 3] == '.')
		return (1);
	return (0);
}
/*
	4 coordenadas: ni más ni menos, no se repiten
	textura para cada coordenada
	- el archivo se puede abrir
	F y C valores entre 0 y 255
*/
int	correct_textures(char *map)
{
	return (1);
}