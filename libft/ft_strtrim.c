/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meru <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:48:28 by meru              #+#    #+#             */
/*   Updated: 2025/04/21 11:12:00 by meru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_newstr(const char *s1, size_t start, size_t len)
{
	char	*str;
	size_t	i;

	if (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[start + i];
		i++;
	}
	return (str);
}

static int	ft_strchar(const char *set, const char s1)
{
	int	z;

	z = 0;
	while (set[z] != '\0')
	{
		if (set[z] == s1)
			return (1);
		z++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int	start;
	int	finish;

	start = 0;
	finish = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (ft_strchar(set, s1[start]))
		start++;
	while (ft_strchar(set, s1[finish]))
		finish--;
	return (ft_newstr(s1, start, finish - (start -1)));
}
