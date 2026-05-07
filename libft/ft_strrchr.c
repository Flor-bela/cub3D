/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:53:37 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/17 18:13:47 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ltr)
{
	int				len;
	unsigned char	z;

	z = (char)ltr;
	len = ft_strlen(str);
	if (ltr == 0)
		return ((char *)&str[len]);
	if (!(*str))
		return (NULL);
	while (len >= 0)
	{
		if (str[len] == z)
			return ((char *)&str[len]);
		len--;
	}
	return (NULL);
}
