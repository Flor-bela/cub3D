/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:38:35 by medel-ca          #+#    #+#             */
/*   Updated: 2025/05/06 18:59:26 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*set_line(char **rest)
{
	char	*line;
	char	*temp;
	size_t	len;

	len = 0;
	if (!rest || !(*rest) || **rest == '\0')
		return (NULL);
	while ((*rest)[len] && (*rest)[len] != '\n')
		len++;
	if ((*rest)[len] == '\n')
		len++;
	line = ft_substr(*rest, 0, len);
	temp = ft_strdup(*rest + len);
	if (!line || !temp)
	{
		free(line);
		free(temp);
		return (NULL);
	}
	free(*rest);
	*rest = temp;
	return (line);
}
 
static char	*fill_line_buffer(int fd, char *rest)
{
	ssize_t	bytes_read;
	char	*temp;
	char	*buffer;

	bytes_read = 1;
	buffer = (char *)malloc((1024 + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 1024);
		if (bytes_read < 0)
		{
			free(buffer);
			if (rest)
				free(rest);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!rest)
		{
			rest = ft_strdup("");
			if (!rest)
				return (free(buffer), NULL);
		}
		temp = ft_strjoin(rest, buffer);
		if (!temp)
		{
			free(buffer);
			free(rest);
			return (NULL);
		}
		free(rest);
		rest = temp;
		if (ft_strchr(buffer, '\n'))
			break;
	}
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*rest;

	if (fd < 0)
		return (NULL);
	rest = fill_line_buffer(fd, rest);
	if (!rest)
		return (NULL);
	if (*rest == '\0')
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	next_line = set_line(&rest);
	if (!next_line)
		return (NULL);
	if (next_line[0] == '\0')
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
