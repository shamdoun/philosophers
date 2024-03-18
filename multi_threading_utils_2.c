/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:53:32 by shamdoun          #+#    #+#             */
/*   Updated: 2024/03/18 06:05:51 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		exit(1);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	display_message(char *message, t_session *s, long value, int id)
{
	if (pthread_mutex_lock(&s->display))
		exit(1);
	if (!s->must_stop)
		printf(message, value, id);
	if (pthread_mutex_unlock(&s->display))
		exit(1);
}

void	update_meal_count(t_philosopher *p)
{
	pthread_mutex_lock(&p->s->meal_lock);
	p->num_meals++;
	pthread_mutex_unlock(&p->s->meal_lock);
}

int	check_if_philo_started_eating(t_session *s, int i)
{
	if (gettime() - s->all_philosophers[i].last_meal_time
		>= s->time_to_die)
	{
		alert_all_to_stop(s, i);
		return (1);
	}
	return (0);
}
