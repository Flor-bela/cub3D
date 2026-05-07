/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:05:25 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/17 17:05:59 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t count)
{
	unsigned char	*s;
	size_t			i;

	s = (unsigned char *)src;
	c = (unsigned char)c;
	i = 0;
	while (i < count)
	{
		if (s[i] == c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
