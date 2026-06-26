/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames_per_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-roch <fda-roch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:25:19 by fda-roch          #+#    #+#             */
/*   Updated: 2026/06/25 14:49:32 by fda-roch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	get_deltatime(struct timeval old_time, struct timeval curr_time)
{
	long	delta_seconds;
	long	delta_useconds;
	double	delta_time;

	delta_seconds = curr_time.tv_sec - old_time.tv_sec;
	delta_useconds = curr_time.tv_usec - old_time.tv_usec;
	delta_time = (double)delta_seconds + (double)(delta_useconds / 1000000.0);
	return (delta_time);
}

void	frames_per_second(void)
{
	static struct timeval	old_time;
	static struct timeval	current_time;
	static int				initialized = 0;
	double					delta_time;
	double					fps;

	if (initialized == 0)
	{
		gettimeofday(&old_time, NULL);
		initialized = 1;
		return ;
	}
	gettimeofday(&current_time, NULL);
	delta_time = get_deltatime(old_time, current_time);
	if (delta_time > 0.01)
	{
		fps = 1.0 / delta_time;
		printf("FPS: %.0f\n", fps);
		old_time = current_time;
	}
}
