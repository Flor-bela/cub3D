/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:41:26 by fda-roch          #+#    #+#             */
/*   Updated: 2025/05/21 14:22:44 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_start_pos(char const *s1, char const *set)
{
	size_t	start;
	size_t	i;
	size_t	j;
	size_t	len_set;

	i = 0;
	j = 0;
	start = 0;
	len_set = ft_strlen(set);
	while (start == 0 && s1[i] != '\0' && set[j] != '\0')
	{
		if (s1[i] == set[j])
		{
			j = 0;
			i++;
		}
		if (s1[i] != set[j])
			j++;
		if (j == len_set)
			start = 1;
	}
	return (i);
}

static size_t	ft_end_pos(char const *s1, char const *set, size_t start_pos)
{
	size_t	i;
	size_t	j;
	size_t	end;
	size_t	len_set;

	i = 0;
	j = 0;
	end = 0;
	len_set = ft_strlen(set);
	i = ft_strlen(s1);
	if (i > 0)
		i--;
	while (end == 0 && i > start_pos && set[j] != '\0')
	{
		if (s1[i] == set[j])
		{
			j = 0;
			i--;
		}
		if (s1[i] != set[j])
			j++;
		if (j == len_set)
			end = 1;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start_pos;
	size_t	end_pos;
	char	*ptr;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	start_pos = ft_start_pos(s1, set);
	end_pos = ft_end_pos(s1, set, start_pos);
	if (start_pos == 0 && end_pos == 0)
		ptr = (char *)malloc(1);
	else
		ptr = (char *)malloc(end_pos - start_pos + 2);
	if (ptr == NULL)
		return (NULL);
	while (start_pos <= end_pos)
	{
		ptr[i] = s1[start_pos];
		start_pos++;
		i++;
	}
	if (i != 1)
		ptr[i] = '\0';
	return (ptr);
}
