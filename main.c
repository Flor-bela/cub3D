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
	while (flag == 1)
	{
		if (str[i - 1] != 'c')
			break ;
		if (str[i - 2] != 'u')
			break ;
		if (str[i - 3] != 'b')
			break ;
		if (str[i - 4] != '.')
			break ;
		flag = 0;
	}
	if (flag == 1)
		return (1);
	return (0);
}

static int	check_file(int argc, char **argv)
{
	int	fd_cub;
	
	if (argc != 2 || argv[1] == NULL || argv[1][0] == '\0')
		return (1);
	if (check_extension(argv[1]) == 0)
		fd_cub = open(argv[1], O_RDONLY);
	else if (check_extension(argv[1]) == 1)
	{
		write(2, "Error\n map isn't valid\n", 24);
		exit (1);
	}
	if (fd_cub < 0)
	{
		perror("Error\n");
		exit(1);
	}
	return (fd_cub);
}

int	main(int argc, char **argv)
{
	int	fd_cub;
	
	fd_cub = check_file(argc, argv);
	


	return (0);
}