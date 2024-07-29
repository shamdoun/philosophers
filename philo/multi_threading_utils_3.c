/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading_utils_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:52:12 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/29 23:37:53 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_usleep(int duration, t_session *s)
{
	long	cur_time;

	cur_time = gettime();
	while (gettime() < (cur_time + duration))
	{
		pthread_mutex_lock(&s->must_stop_lock);
		if (s->must_stop)
		{
			pthread_mutex_unlock(&s->must_stop_lock);
			return ;
		}
		pthread_mutex_unlock(&s->must_stop_lock);
		usleep(100);
	}
}
