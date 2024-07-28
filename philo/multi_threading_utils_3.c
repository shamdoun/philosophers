/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading_utils_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:52:12 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 17:13:15 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_usleep(int duration, t_session *s)
{
	long	cur_time;

	cur_time = gettime();
	while (1)
	{
		pthread_mutex_lock(&s->must_stop_lock);
		if (s->must_stop)
		{
			pthread_mutex_unlock(&s->must_stop_lock);
			return ;
		}
		pthread_mutex_unlock(&s->must_stop_lock);
		if (gettime() < (cur_time + duration))
			return ;
		usleep(100);
	}
}
