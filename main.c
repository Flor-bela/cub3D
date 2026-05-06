#include "cub3D.h"

static int	check_extension(const char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (str == NULL)
		return (1);
	i = ft_strlen(str);
	

	return (i);
}



static int	check_file(int argc, char **argv)
{
	if (argc != 2 || argv[1] == NULL || argv[1][0] == '\0')
		return (1);
	
	



	return (check_file_cub(argv[1]));

}





int	main(int argc, char **argv)
{
	int	fd_cub;
	
	fd_cub = check_file(argc, argv);



	return (0);
}