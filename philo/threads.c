/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:08:27 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/29 21:45:35 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_philo_threads(t_session info)
{
	int	i;

	i = 0;
	while (i < info.nbr_philosophers)
	{
		info.all_philosophers[i].last_meal_time = gettime();
		if (pthread_create(&info.all_philosophers[i].thread, NULL,
				&routines, &info.all_philosophers[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	join_all_threads(t_session info, t_philosopher monitor)
{
	int	i;

	i = 0;
	if (pthread_join(monitor.thread, NULL))
		return (1);
	while (i < info.nbr_philosophers)
	{
		if (pthread_join(info.all_philosophers[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}

static void	execute_2(t_philosopher *p, char *m, int mode)
{
	if (mode == 3)
	{
		pthread_mutex_unlock(&p->s->must_stop_lock);
		display_message(m, p->s, gettime() - p->s->start_time, p->id);
		my_usleep(p->s->time_to_sleep, p->s);
	}
	else if (mode == 4)
	{
		pthread_mutex_unlock(&p->s->must_stop_lock);
		display_message(m, p->s, gettime() - p->s->start_time, p->id);
	}
	else if (mode == 5)
	{
		display_message(m, p->s, gettime() - p->s->start_time, p->id);
		update_last_meal_time(p);
		update_meal_count(p);
		my_usleep(p->s->time_to_eat, p->s);
	}
}

void	execute_eating_routine(t_philosopher *p)
{
	if (!p->s->max_num_meals)
		my_usleep(p->s->time_to_die, p->s);
	else
		execute_2(p, "%ld %d is eating\n", 5);
}

int	execute_1(t_philosopher *p, char *m, int mode)
{
	pthread_mutex_lock(&p->s->must_stop_lock);
	if (!p->s->must_stop)
	{
		if (mode == 1)
		{
			pthread_mutex_unlock(&p->s->must_stop_lock);
			pthread_mutex_lock(p->left_fork);
			display_message(m, p->s, gettime() - p->s->start_time, p->id);
		}
		else if (mode == 2)
		{
			pthread_mutex_unlock(&p->s->must_stop_lock);
			pthread_mutex_lock(&p->right_fork);
			display_message(m, p->s, gettime() - p->s->start_time, p->id);
			execute_eating_routine(p);
		}
		else
			execute_2(p, m, mode);
	}
	else
	{
		pthread_mutex_unlock(&p->s->must_stop_lock);
		return (0);
	}
	return (1);
}
