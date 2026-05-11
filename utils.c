#include "cub3D.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*ft_strcpy(char *str, int size)
{
	int		i;
	char	*cpy;

	cpy = malloc(size + 1);
	i = 0;
	if (!cpy)
		return (NULL);
	while (str[i] && i < size)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	ft_format(char *file)
{
	size_t	len;

	len = ft_strlen(file) - 1;
	if (file[len] == 'b' && file[len - 1] == 'u'
		&& file[len - 2] == 'c' && file[len - 3] == '.')
		return (1);
	return (0);
}

int	empty_line(char *line)
{
	if (!line)
		return (0);
	if (ft_isspace(*line) || *line == '\n')
	{
		line++;
		return (1);
	}
	return (0);
}