/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:50:18 by medel-ca          #+#    #+#             */
/*   Updated: 2026/05/15 15:50:18 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	errormsg(char *errmsg, int errnum)
{
	if (errmsg != 0 || errnum != 0)
		ft_putendl_fd("Error", 2);
	if (errmsg != 0)
		ft_putstr_fd(errmsg, 2);
	if (errmsg != 0 && errnum != 0)
		ft_putstr_fd(": ", 2);
	if (errnum != 0)
		ft_putstr_fd(strerror(errnum), 2);
	if (errmsg != 0 || errnum != 0)
	{
		ft_putendl_fd("", 2);
		exit(1);
	}
	exit(0);
}
