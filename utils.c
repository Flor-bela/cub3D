/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 16:09:51 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/17 14:06:07 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ret = ft_calloc(len + 1, sizeof(char));
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
	free(s1);
	return (ret);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
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

int	new_line(char *line)
{
	if (!line)
		return (0);
	if (*line == '\n')
	{
		line++;
		return (1);
	}
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
