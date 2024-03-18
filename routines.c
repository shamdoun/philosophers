/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:54:09 by shamdoun          #+#    #+#             */
/*   Updated: 2024/03/18 06:26:58 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philo_eats(t_philosopher *p)
{
	if (!execute_1(p, "%ld %d has taken a fork\n", 1))
		return (1);
	if (!execute_1(p, "%ld %d has taken a fork\n", 2))
	{
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(&p->right_fork);
	return (0);
}

static void	*special_case(t_philosopher *p)
{
	if (!execute_1(p, "%ld %d has taken a fork\n", 2))
		return (NULL);
	usleep(p->s->time_to_die * 1000);
	return (NULL);
}

void	attempt_to_lock_unlock(pthread_mutex_t *m, int mode)
{
	if (!mode)
	{
		if (pthread_mutex_lock(m))
			exit(1);
	}
	else
	{
		if (pthread_mutex_unlock(m))
			exit(1);
	}
}

void	*monitor_routine(void *data)
{
	int			i;
	t_session	*s;
	size_t		time;

	i = 0;
	s = (t_session *)data;
	while (1)
	{
		i = 0;
		time = gettime();
		while (i < s->nbr_philosophers)
		{
			if (time - s->all_philosophers[i].last_meal_time >= s->time_to_die
				&& check_if_philo_started_eating(s, i))
				break ;
			i++;
		}
		if (i != s->nbr_philosophers || check_number_of_meals(s))
			break ;
	}
	return (NULL);
}

void	*routines(void *data)
{
	t_philosopher	*p;

	p = (t_philosopher *)data;
	if (p->id % 2 == 0)
		usleep(15000);
	if (p->s->nbr_philosophers == 1)
		return (special_case(p));
	while (!simulation_must_stop(p->s))
	{
		if (philo_eats(p))
			break ;
		if (!execute_1(p, "%ld %d is sleeping\n", 3))
			break ;
		if (!execute_1(p, "%ld %d is thinking\n", 4))
			break ;
	}
	return (NULL);
}
