/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:54:06 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/18 16:03:26 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *lstr, const char *sstr, size_t size)
{
	size_t	i;
	size_t	z;

	if (!*sstr)
		return ((char *)lstr);
	i = 0;
	while (lstr[i] != '\0')
	{
		z = 0;
		while (lstr[i] == sstr[z] && sstr[z] && i < size)
		{
			i++;
			z++;
		}
		if (sstr[z] == '\0')
			return ((char *)&lstr[i - z]);
		i = i - z + 1;
	}
	return (NULL);
}
