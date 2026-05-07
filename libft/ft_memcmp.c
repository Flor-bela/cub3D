/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meru <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:01:58 by meru              #+#    #+#             */
/*   Updated: 2025/04/11 18:03:39 by meru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *lstr, const void *sstr, size_t count)
{
	unsigned const char	*l;
	unsigned const char	*s;
	size_t				i;

	l = (unsigned char *)lstr;
	s = (unsigned char *)sstr;
	i = 0;
	while (i < count)
	{
		if (l[i] != s[i])
			return (l[i] - s[i]);
		i++;
	}
	return (0);
}
