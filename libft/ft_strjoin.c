/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:03:55 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/18 16:29:49 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*newstr;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		newstr = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (newstr == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			newstr[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			newstr[len1] = s2[i];
			len1++;
		}
		newstr[len1] = '\0';
		return (newstr);
	}
	return (NULL);
}
