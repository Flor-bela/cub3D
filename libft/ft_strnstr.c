/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:03:10 by fda-roch          #+#    #+#             */
/*   Updated: 2025/05/21 14:33:25 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	go_back(size_t *i, size_t *j, size_t *len)
{
	*i = *i - *j + 1;
	*len += *j - 1;
	*j = 0;
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_l;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	len_l = ft_strlen(little);
	while (len > 0 && big[i] != '\0' && little[j] != '\0' && j != len_l)
	{
		if (big[i] != little[j])
		{
			if (j > 0)
				go_back(&i, &j, &len);
			j = 0;
		}
		if (big[i] == little[j])
			j++;
		i++;
		len--;
	}
	if (j == len_l)
		return ((char *)&big[i - len_l]);
	return (NULL);
}
