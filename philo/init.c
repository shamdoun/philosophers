/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:45:57 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 17:17:52 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_forks(t_session *info)
{
	int	i;	

	i = 0;
	while (i < info->nbr_philosophers)
	{
		if (pthread_mutex_init(&info->all_philosophers[i].right_fork, NULL))
		{
			free(info->all_philosophers);
			//destroy mutexes
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < info->nbr_philosophers)
	{
		info->all_philosophers[i].id = i + 1;
		info->all_philosophers[i].s = info;
		if (i)
			info->all_philosophers[i].left_fork
				= &info->all_philosophers[i - 1].right_fork;
		if (i == info->nbr_philosophers - 1)
			info->all_philosophers[0].left_fork
				= &info->all_philosophers[i].right_fork;
		i++;
	}
	return (0);
}

static void	init_mutexes(t_session *info)
{
	pthread_mutex_init(&info->display, NULL);
	pthread_mutex_init(&info->must_stop_lock, NULL);
	pthread_mutex_init(&info->last_time_lock, NULL);
	pthread_mutex_init(&info->meal_lock, NULL);
}

void	destroy_mutexes(t_session *info)
{
	pthread_mutex_destroy((&info->display));
	pthread_mutex_destroy((&info->must_stop_lock));
	pthread_mutex_destroy((&info->last_time_lock));
	pthread_mutex_destroy((&info->meal_lock));
}

int	init(t_session *info, char **argv)
{
	info->nbr_philosophers = ft_atoi(argv[1]);
	if (info->nbr_philosophers < 0)
		return (1);
	info->time_to_die = ft_atoi(argv[2]);
	if (info->time_to_die < 0)
		return (1);
	info->time_to_eat = ft_atoi(argv[3]);
	if (info->time_to_eat < 0)
		return (1);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->time_to_sleep < 0)
		return (1);
	if (argv[5])
		info->max_num_meals = ft_atoi(argv[5]);
	else
		info->max_num_meals = -1;
	info->must_stop = 0;
	info->start_time = gettime();
	init_mutexes(info);
	info->all_philosophers
		= malloc(sizeof(t_philosopher) * info->nbr_philosophers);
	if (!info->all_philosophers)
	{
		destroy_mutexes(info);
		return (1);
	}
	if (init_forks(info))
	{
		destroy_mutexes(info);
		return (1);
	}
	return (0);
}
