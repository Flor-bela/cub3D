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
		if (str[i - 1] != 'b')
			break ;
		if (str[i - 2] != 'u')
			break ;
		if (str[i - 3] != 'c')
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
	
	fd_cub = 0;
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

static void	check_rows(int fd, char *argv, t_data *map)
{
	char	*line_map;
	int		i;

	i = 0;
	while (1) // ver cuantas lineas tenemos para poder crear la matriz para guardarlo todo
	{
		line_map = get_next_line(fd);
		if (line_map == NULL)
			break;
		i++;
	}
	map->map_arr = (char **)malloc(sizeof (char *) * (i + 1));
	if (map->map_arr == NULL)
	{
		write(2, "Error\n malloc failed\n", 22);
		exit(1);
	}
	map->map_arr[i] = NULL;
	close(fd);
	// abrir de nuevo para ahora sí tenerlo guardado
	fd = open(argv, O_RDONLY);
	i = 0;
	while (1)
	{
		line_map = get_next_line(fd);
		if (line_map == NULL)
			break ;
		map->map_arr[i] = line_map;
		i++;
	}
}


int	main(int argc, char **argv)
{
	int		fd;
	t_data	map;
	
	fd = check_file(argc, argv);
	check_rows(fd, argv[1], &map); // no he bien check...es mas copy...ver que nombre darle
	


	// free map!
	return (0);
}