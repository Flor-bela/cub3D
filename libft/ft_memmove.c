/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:35:32 by fda-roch          #+#    #+#             */
/*   Updated: 2025/05/21 14:33:11 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*u_dest;
	unsigned char	*u_src;
	size_t			i;
	size_t			j;

	i = 0;
	u_dest = (unsigned char *)dest;
	u_src = (unsigned char *)src;
	j = n - 1;
	while (n > 0)
	{
		if (u_dest > u_src)
		{
			u_dest[j] = u_src[j];
			j--;
		}
		if (u_dest <= u_src)
		{
			u_dest[i] = u_src[i];
			i++;
		}
		n--;
	}
	return (dest);
}
