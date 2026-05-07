/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meru <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:20:19 by meru              #+#    #+#             */
/*   Updated: 2025/04/17 17:22:51 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc(int numlen)
{
	char	*mnumber;

	mnumber = malloc(sizeof(char) * (numlen + 1));
	if (!(mnumber))
		return (NULL);
	mnumber[numlen] = '\0';
	return (mnumber);
}

static int	ft_numlen(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		numlen;

	numlen = ft_numlen(n) -1;
	number = ft_malloc(numlen + 1);
	if (!number)
		return (NULL);
	if (n == 0)
		number[0] = '0';
	if (n < 0)
	{
		number[0] = '-';
		if (n == -2147483648)
		{
			number[numlen--] = '8';
			n /= 10;
		}
		n = n * -1;
	}
	while (n > 0)
	{
		number[numlen--] = n % 10 + '0';
		n = n / 10;
	}
	return (number);
}
