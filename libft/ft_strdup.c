/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:54:43 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/17 17:55:20 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	z;
	char	*cpy;

	z = 0;
	i = ft_strlen(str);
	cpy = (char *)malloc(i + 1);
	if (cpy == NULL)
		return (NULL);
	while (z < i)
	{
		cpy[z] = str[z];
		z++;
	}
	cpy[z] = '\0';
	return (cpy);
}
