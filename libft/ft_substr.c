/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meru <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:27:36 by meru              #+#    #+#             */
/*   Updated: 2025/04/21 12:28:13 by meru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	z;

	if (!(s))
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup (""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	subs = ft_calloc (len + 1, sizeof(char));
	if (subs == NULL)
		return (NULL);
	z = 0;
	while (z < len && s[start + z])
	{
		subs[z] = s[start + z];
		z++;
	}
	return (subs);
}
