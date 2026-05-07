#include "cub3D.h"

int main(int ac, char **av)
{
	if(ac != 2)
	{
		write (1, "Usage: ./cub3D map.cub\n", 24);
		return (1);
	}
	if(!ft_format(av[1]))
	{
		write(1, "Correct format is .cub\n", 24);
		return 1;
	}
	char *map = read_file(av[1]);
	if(!correct_textures(map))
	{
		printf("Some mistakes in the textures\n");
		free(map);
		return 1;
	}
	printf("Correct file!\n");
	free(map);
	return 0;
}