/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:39:36 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/17 17:40:50 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = dest;
	while (i < count)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}
