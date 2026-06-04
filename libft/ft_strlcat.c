/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:56:55 by fda-roch          #+#    #+#             */
/*   Updated: 2025/05/21 14:31:04 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	z;
	size_t	len_dst;
	size_t	len_src;
	size_t	to_append;

	z = 0;
	to_append = 0;
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (len_dst > size)
		return (len_src + size);
	if (len_dst == size)
		return (len_src + len_dst);
	to_append = size - len_dst - 1;
	len_src = len_src + len_dst;
	while (src[z] != '\0' && to_append > 0)
	{
		dst[len_dst] = src[z];
		len_dst++;
		z++;
		to_append--;
	}
	dst[len_dst] = '\0';
	return (len_src);
}
