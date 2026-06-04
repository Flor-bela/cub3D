/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:08:48 by fda-roch          #+#    #+#             */
/*   Updated: 2025/05/20 09:54:38 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;
	const char		*ptr;

	i = 0;
	ch = c;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == ch)
		{
			ptr = &s[i];
			return ((char *)ptr);
		}
		i--;
	}
	return (NULL);
}
