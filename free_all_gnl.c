/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:33:41 by fda-roch          #+#    #+#             */
/*   Updated: 2026/05/06 16:34:07 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	free_all_gnl(char **ptr, char **result)
{
	if (*result != NULL)
		free (*result);
	*result = NULL;
	if (*ptr != NULL)
		free (*ptr);
	*ptr = NULL;
	return (-1);
}
