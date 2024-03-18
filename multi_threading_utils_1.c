/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading_utils_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:51:00 by shamdoun          #+#    #+#             */
/*   Updated: 2024/03/18 06:25:00 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	alert_all_to_stop(t_session *s, int i)
{
	s->must_stop = 1;
	if (pthread_mutex_unlock(&s->must_stop_lock))
		exit(1);
	if (pthread_mutex_lock(&s->display))
		exit(1);
	printf("%ld %d died\n", gettime() - s->start_time,
		s->all_philosophers[i].id);
	if (pthread_mutex_unlock(&s->display))
		exit(1);
}

int	check_number_of_meals(t_session *s)
{
	size_t	sum;
	int		i;

	i = 0;
	sum = 0;
	if (pthread_mutex_lock(&s->meal_lock))
		exit(1);
	while (s->max_num_meals && i < s->nbr_philosophers)
	{
		sum += s->all_philosophers[i].num_meals;
		i++;
	}
	if (s->max_num_meals && sum == s->max_num_meals * s->nbr_philosophers)
	{
		s->must_stop = 1;
		if (pthread_mutex_unlock(&s->meal_lock))
			exit(1);
		return (1);
	}
	if (pthread_mutex_unlock(&s->meal_lock))
		exit(1);
	return (0);
}

int	simulation_must_stop(t_session *s)
{
	pthread_mutex_lock(&s->must_stop_lock);
	if (s->must_stop)
	{
		pthread_mutex_unlock(&s->must_stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&s->must_stop_lock);
	return (0);
}

void	update_last_meal_time(t_philosopher *p)
{
	pthread_mutex_lock(&p->s->last_time_lock);
	p->last_meal_time = gettime();
	pthread_mutex_unlock(&p->s->last_time_lock);
}
