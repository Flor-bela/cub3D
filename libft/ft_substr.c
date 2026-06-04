/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:00:46 by fda-roch          #+#    #+#             */
/*   Updated: 2025/05/21 15:04:02 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ptr;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	if (start > i)
	{
		ptr = (char *)malloc(1);
		if (ptr == NULL)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	if (i - start >= len)
		i = len + 1;
	else
		i = i - start + 1;
	ptr = (char *)malloc(i);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, &s[start], i);
	return (ptr);
}
