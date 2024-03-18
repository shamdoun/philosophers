/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:44:17 by shamdoun          #+#    #+#             */
/*   Updated: 2024/03/18 04:28:03 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_session			info;
	t_philosopher		monitor;

	if (argc < 5 || argc > 6)
		return (1);
	init(&info, argv);
	create_philo_threads(info);
	if (pthread_create(&monitor.thread, NULL, &monitor_routine, &info) == -1)
	{
		free(info.all_philosophers);
		exit(1);
	}
	join_all_threads(info, monitor);
	return (0);
}
