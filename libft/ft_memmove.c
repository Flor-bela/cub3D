/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:36:34 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/16 20:19:00 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned const char *)src;
	i = 0;
	if (d == s)
		return (dest);
	if (d < s || d >= (s + count))
	{
		while (i < count)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (count-- > 0)
			d[count] = s[count];
	}
	return (dest);
}
