/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:59:41 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/18 13:44:29 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *str, size_t size)
{
	size_t	i;
	size_t	ldest;
	size_t	lstr;

	ldest = ft_strlen(dest);
	lstr = ft_strlen(str);
	if (size <= ldest)
		return (size + lstr);
	i = 0;
	while (str[i] && (ldest + i + 1) < size)
	{
		dest[ldest + i] = str[i];
		i++;
	}
	dest[ldest + i] = '\0';
	return (ldest + lstr);
}
