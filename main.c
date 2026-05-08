#include "cub3D.h"

static void	free_map(t_data *map)
{
	int	i;

	i = 0;	
	while (i < map->total_rows)
	{
		free(map->map_arr[i]);
		i++;
	}
	free(map->map_arr);
}

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
		write(2, "Error \n map isn't valid\n", 24);
		exit (1);
	}
	if (fd_cub < 0)
	{
		perror("Error \n");
		exit(1);
	}
	return (fd_cub);
}

static void	load_map(int fd, char *argv, t_data *map)
{
	char	*line_map;
	int		i;

	i = 0;
	while (1) // ver cuantas lineas tenemos para poder crear la matriz para guardarlo todo
	{
		line_map = get_next_line(fd); // aqui el fd ya viene de Mercedes
		if (line_map == NULL)
			break;
		free(line_map);
		i++;
	}
	map->total_rows = i; // number of rows that map has!
	map->map_arr = (char **)malloc(sizeof (char *) * (i + 1));
	if (map->map_arr == NULL)
	{
		write(2, "Error \n malloc failed\n", 22);
		exit(1);
	}
	map->map_arr[i] = NULL;
		close(fd); // ya lo cierro yo aquí

	fd = open(argv, O_RDONLY); // vuelvo a abrirlo
	i = 0;
	// to do: debería aquí añadir que pase todas las rows que Mercedes ha tenido que leer para llegar a mi parte
	// loop para que continue solo en la parte del mapa
	while (1)
	{
		line_map = get_next_line(fd); //
		if (line_map == NULL)
			break ;
		map->map_arr[i] = line_map;
		i++;
	}
}


static void	check_characters_map(t_data *map) // tab??? should I add it??
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (i < map->total_rows) // hmmm tiene salto de línea!!!!! Tengo que quitarlo!!! No debería ser interpretado
	{
		j = 0;
		while (map->map_arr[i][j] != '\0')
		{
			if (map->map_arr[i][j] == 'N' || map->map_arr[i][j] == 'S'
				 || map->map_arr[i][j] == 'W' || map->map_arr[i][j] == 'E')
			{
				map->player.col = j;
				map->player.row = i;
				flag++;
				j++;
			}
			else if (map->map_arr[i][j] == ' ' || map->map_arr[i][j] == '\n'
				|| map->map_arr[i][j] == '1' || map->map_arr[i][j] == '0')
				j++;
			else
			{
				write(2, "Error \n incorrect character on the map.", 40);
				free_map(map);
				exit (1);
			}
		}
		i++;
	}
	if (flag != 1)
	{
		write(2, "Error \n incorrect starting point.", 33);
		free_map(map);
		exit (1);
	}
}

static void	error_walls(t_data *map)
{
	write(2, "Error \n map not enclosed by walls.\n", 36);
	free_map(map);
	exit(1);
}

static void	check_map_enclosed(t_data *map)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	while (i < map->total_rows)
	{
		j = 0;
		while (map->map_arr[i][j] != '\0')
		{
			if (map->map_arr[i][j] == '0')
			{
				flag = 0;
				if ((j + 1) < (int)ft_strlen(map->map_arr[i]))
				{
					flag++;
					if (map->map_arr[i][j + 1] == ' ' || map->map_arr[i][j + 1] == '\n')
						error_walls(map);
				}
				if ((j - 1) >= 0)
				{
					flag++;
					if (map->map_arr[i][j - 1] == ' ' || map->map_arr[i][j - 1] == '\n')
						error_walls(map);
				}
				if ((i - 1) >= 0)
				{	
					flag++;
					if (map->map_arr[i - 1][j] == ' ' || map->map_arr[i - 1][j] == '\n')
						error_walls(map);
				}
				if ((i + 1) < map->total_rows)
				{
					flag++;
					if (map->map_arr[i + 1][j] == ' ' || map->map_arr[i + 1][j] == '\n')
						error_walls(map);
				}
				if (flag != 4)
					error_walls(map);
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_data	map;
	
	map.map_arr = NULL;
	fd = check_file(argc, argv); // Mercedes ya tiene esta parte
	// Cuando ella acabe de leer su parte yo puedo continuar a leer el fd y así voy continuando hasta la zona el mapa....
	load_map(fd, argv[1], &map);
	check_characters_map(&map);
	check_map_enclosed(&map);


	free_map(&map);
	return (0);
}