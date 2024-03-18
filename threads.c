/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:08:27 by shamdoun          #+#    #+#             */
/*   Updated: 2024/03/18 04:27:40 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philo_threads(t_session info)
{
	int	i;

	i = 0;
	while (i < info.nbr_philosophers)
	{
		info.all_philosophers[i].last_meal_time = gettime();
		if (pthread_create(&info.all_philosophers[i].thread, NULL,
				&routines, &info.all_philosophers[i]) == -1)
		{
			free(info.all_philosophers);
			exit(1);
		}
		i++;
	}
}

void	join_all_threads(t_session info, t_philosopher monitor)
{
	int	i;

	i = 0;
	if (pthread_join(monitor.thread, NULL))
	{
		free(info.all_philosophers);
		exit(1);
	}
	while (i < info.nbr_philosophers)
	{
		if (pthread_join(info.all_philosophers[i].thread, NULL))
		{
			free(info.all_philosophers);
			exit(1);
		}
		i++;
	}
}

static void	execute_2(t_philosopher *p, char *m, int mode)
{
	if (mode == 3)
	{
		pthread_mutex_unlock(&p->s->must_stop_lock);
		display_message(m, p->s, gettime(p->s) - p->s->start_time, p->id);
		usleep(p->s->time_to_sleep * 1000);
	}
	else if (mode == 4)
	{
		pthread_mutex_unlock(&p->s->must_stop_lock);
		display_message(m, p->s, gettime(p->s) - p->s->start_time, p->id);
	}
	else if (mode == 5)
	{
		if (p->s->max_num_meals > 0)
		{
			pthread_mutex_unlock(&p->s->must_stop_lock);
			update_last_meal_time(p);
			display_message(m, p->s, gettime(p->s) - p->s->start_time, p->id);
			update_meal_count(p);
			usleep(p->s->time_to_eat * 1000);
		}
		else
			pthread_mutex_unlock(&p->s->must_stop_lock);
	}
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
			display_message(m, p->s, gettime(p->s) - p->s->start_time, p->id);
		}
		else if (mode == 2)
		{
			pthread_mutex_unlock(&p->s->must_stop_lock);
			pthread_mutex_lock(&p->right_fork);
			display_message(m, p->s, gettime(p->s) - p->s->start_time, p->id);
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
