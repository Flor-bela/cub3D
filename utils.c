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