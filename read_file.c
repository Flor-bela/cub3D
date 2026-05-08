#include "cub3D.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(len + 1 * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	free(s1);
	return (ret);
}

char	*set_line(char **rest)
{
	char	*line;
	char	*temp;
	int		i;

	if (!rest || !*rest || !**rest)
		return (NULL);
	temp = *rest;
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line = ft_strcpy(temp, i);
	if (!line)
	{
		free(*rest);
		return (NULL);
	}
	temp = ft_strcpy(*rest + i, ft_strlen(*rest + i));
	free(*rest);
	*rest = temp;
	return (line);
}

char	*fill_buffer(int fd, char *rest)
{
	char	buffer[1024 + 1];
	int		bytes;

	while ((bytes = read(fd, buffer, 1024)) > 0)
	{
		if (!rest)
		{
			rest = malloc(1);
			if (!rest)
				return (NULL);
			rest[0] = '\0';
		}
		buffer[bytes] = '\0';
		rest = ft_strjoin_free(rest, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (bytes == -1)
		return (NULL);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;

	if (fd < 0)
		return (NULL);
	rest = fill_buffer(fd, rest);
	if (!rest)
	{
		free(rest);
		return (NULL);
	}
	line = set_line(&rest);
	return (line);
}
