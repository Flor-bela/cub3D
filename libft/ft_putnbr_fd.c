/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:44:14 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/17 17:44:18 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;

	nbr = n;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		write (fd, "-", 1);
	}
	if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd((nbr % 10) + '0', fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}
