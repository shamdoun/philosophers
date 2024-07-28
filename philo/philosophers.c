/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:44:17 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 17:18:27 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_session			info;
	t_philosopher		monitor;

	if (argc < 5 || argc > 6)
		return (1);
	if (init(&info, argv))
		return (1);
	if (create_philo_threads(info))
	{
		free(info.all_philosophers);
		destroy_mutexes(&info);
		return (1);
	}
	if (pthread_create(&monitor.thread, NULL, &monitor_routine, &info) == -1)
	{
		free(info.all_philosophers);
		destroy_mutexes(&info);
		return (1);
	}
	if (join_all_threads(info, monitor))
	{
		free(info.all_philosophers);
		destroy_mutexes(&info);
		return (1);
	}
	free(info.all_philosophers);
	destroy_mutexes(&info);
	return (0);
}
