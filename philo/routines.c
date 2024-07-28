/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:54:09 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 16:58:48 by shamdoun         ###   ########.fr       */
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
	if (!execute_1(p, "%ld %d has taken a fork\n", 1))
		return (NULL);
	my_usleep(p->s->time_to_die, p->s);
	return (NULL);
}

void	*monitor_routine(void *data)
{
	int			i;
	t_session	*s;
	size_t		time;

	s = (t_session *)data;
	while (1)
	{
		i = 0;
		time = gettime();
		while (i < s->nbr_philosophers)
		{
			pthread_mutex_lock(&s->last_time_lock);
			if (time - s->all_philosophers[i].last_meal_time >= s->time_to_die
				&& check_if_philo_started_eating(s, i))
			{
				pthread_mutex_unlock(&s->last_time_lock);
				break ;
			}
			pthread_mutex_unlock(&s->last_time_lock);
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
		my_usleep(1, p->s);
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
