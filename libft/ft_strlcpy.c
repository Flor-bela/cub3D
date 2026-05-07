/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:08:40 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/18 13:43:47 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *str, size_t size)
{
	size_t	i;
	size_t	lstr;

	lstr = ft_strlen(str);
	if (size == 0)
		return (lstr);
	i = 0;
	while (str[i] != '\0' && i < (size - 1))
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (lstr);
}
