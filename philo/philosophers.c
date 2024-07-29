/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:44:17 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/30 00:15:52 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_all(t_session *info)
{
	int	i;

	i = 0;
	destroy_mutexes(info);
	while (i < info->nbr_philosophers)
	{
		pthread_mutex_destroy(&info->all_philosophers[i].right_fork);
		i++;
	}
	free(info->all_philosophers);
	return (1);
}

int	main(int argc, char **argv)
{
	t_session			info;
	t_philosopher		monitor;
	int					i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (1);
	if (init(&info, argv))
		return (1);
	if (create_philo_threads(info))
		return (free_all(&info));
	if (pthread_create(&monitor.thread, NULL, &monitor_routine, &info) == -1)
		return (free_all(&info));
	if (join_all_threads(info, monitor))
		return (free_all(&info));
	while (i < info.nbr_philosophers)
	{
		pthread_mutex_destroy(&info.all_philosophers[i].right_fork);
		i++;
	}
	destroy_mutexes(&info);
	free(info.all_philosophers);
	return (0);
}
