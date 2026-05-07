#include "cub3D.h"

char	*fill_buffer(char *rest, int fd)
{
	ssize_t	bytes_read;
	char	*temp;
	char	buffer[1024 + 1];

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 1024);
		if (bytes_read < 0)
			return (free(rest), NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		temp = ft_strjoin(rest, buffer);
		if (!temp)
			return (free(rest), NULL);
		free(rest);
		rest = temp;
	}
	return (rest);
}

char	*read_file(char *filename)
{
	int		fd;
	char	*rest;
	char	*openf;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		errormsg("No se pudo abrir el archivo", errno);
	}
	rest = ft_calloc(1, 1);
	if (!rest)
	{
		close(fd);
		errormsg("map_init(): ft_calloc()", errno);
	}
	openf = fill_buffer(rest, fd);
	if (!openf)
	{
		errormsg("No se pudo leer el archivo", errno);
	}
	close(fd);
	return (openf);
}