/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:21:14 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/21 18:05:21 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ltr)
{
	int				i;
	int				len;
	unsigned char	z;

	z = (char)ltr;
	len = ft_strlen(str);
	if (z == 0)
		return ((char *)&str[len]);
	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (i <= len)
	{
		if (str[i] == z)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
