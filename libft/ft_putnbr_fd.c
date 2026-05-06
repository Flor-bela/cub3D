/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:08:15 by fda-roch          #+#    #+#             */
/*   Updated: 2025/05/20 17:39:47 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countdigits_sign(int *n, int *sign, long *num)
{
	int	counter;

	counter = 0;
	if (*n < 0)
	{
		*sign = 1;
		*num = -*num;
	}
	while (*n != 0)
	{
		*n = *n / 10;
		counter++;
	}
	if (*sign == 0)
		counter--;
	return (counter);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		counter;
	long	num;
	int		sign;
	char	ptr[12];

	num = n;
	sign = 0;
	if (n == 0)
		write(fd, "0", 1);
	counter = countdigits_sign(&n, &sign, &num);
	ptr[counter + 1] = '\0';
	while (num > 0)
	{
		ptr[counter] = (num % 10) + '0';
		num = num / 10;
		counter--;
	}
	if (sign == 0)
		write(fd, &ptr, ft_strlen(ptr));
	if (sign == 1)
	{
		ptr[counter] = '-';
		write(fd, &ptr, ft_strlen(ptr));
	}
}
