/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:00:28 by fda-roch          #+#    #+#             */
/*   Updated: 2026/05/08 17:43:09 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ptr_exists(char **ptr, char **result)
{
	*result = (char *)malloc(ft_len(*ptr) + 1);
	if (*result == NULL)
	{
		if (*ptr != NULL)
			free (*ptr);
		*ptr = NULL;
		return (-1);
	}
	ft_copy(*result, *ptr, ft_len(*ptr) + 1);
	free (*ptr);
	*ptr = NULL;
	return (0);
}

static int	bytes_exist(char **temp_result, char **result, char *buffer)
{
	*temp_result = (char *)malloc(ft_len(*result) + ft_len(buffer) + 1);
	if (*temp_result == NULL)
	{
		free (*result);
		*result = NULL;
		return (-1);
	}
	ft_copy(*temp_result, *result, ft_len(*result) + 1);
	ft_strlcat(*temp_result, buffer, ft_len(*result) + ft_len(buffer) + 1);
	if (*result != NULL)
	{
		free (*result);
		*result = NULL;
	}
	*result = *temp_result;
	return (0);
}

static int	nwln_exists(char *ptr_nwln, char **temp_result, char **result, char **ptr)
{
	if (*result == NULL)
		return (-1);
	if (((ft_len(ptr_nwln) - 1) + 1) > 1)
	{
		*ptr = (char *)malloc((ft_len(ptr_nwln) - 1) + 1);
		if (*ptr == NULL)
		{
			free (*result);
			return (-1);
		}
		ft_copy(*ptr, ptr_nwln + 1, ft_len(ptr_nwln) + 1);
	}
	*temp_result = (char *)malloc(ft_len(*result) - (ft_len(ptr_nwln) - 1) + 1);
	if (*temp_result == NULL)
		return (free_all_gnl(ptr, result));
	ft_copy(*temp_result, *result, ft_len(*result)
		- (ft_len(ptr_nwln) - 1) + 1);
	free (*result);
	*result = *temp_result;
	return (0);
}

static int	read_bytes(int fd, char **ptr, char **result, char **temp_result)
{
	static char		buffer[BUFFER_SIZE + 1];
	ssize_t			bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes == -1)
	{
		if (*ptr != NULL)
			free (*ptr);
		*ptr = NULL;
		if (*result != NULL)
		{
			free (*result);
			*result = NULL;
			return (-1);
		}
	}
	if (bytes > 0)
	{
		buffer[bytes] = '\0';
		if ((bytes_exist(temp_result, result, buffer) == -1))
			return (-1);
	}
	return (bytes);
}

char	*get_next_line(int fd)
{
	char			*result;
	char			*temp_result;
	static char		*ptr;

	if (fd < 0)
		return (NULL);
	result = NULL;
	while (1)
	{
		if (ptr != NULL)
		{
			if (ptr_exists(&ptr, &result) == -1)
				return (NULL);
		}
		else if (read_bytes(fd, &ptr, &result, &temp_result) <= 0)
			return (result);
		if (ft_strchr(result, '\n') != NULL)
		{
			if (nwln_exists(ft_strchr(result, '\n'),
					&temp_result, &result, &ptr) == -1)
				return (NULL);
			break ;
		}
	}
	return (result);
}
