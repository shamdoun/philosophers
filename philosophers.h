/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:16:44 by shamdoun          #+#    #+#             */
/*   Updated: 2024/03/18 06:05:12 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <libc.h>

typedef struct cycle
{
	int				nbr_philosophers;
	int				must_stop;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			max_num_meals;
	struct philo	*all_philosophers;
	pthread_mutex_t	display;
	pthread_mutex_t	must_stop_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	last_time_lock;
}	t_session;

typedef struct philo
{
	int				id;
	t_session		*s;
	size_t			last_meal_time;
	size_t			num_meals;
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
}	t_philosopher;

int		ft_atoi(const char *str);
void	init(t_session *info, char **argv);
long	gettime(void);
void	*routines(void *data);
void	*monitor_routine(void *data);
void	*monitor_routine(void *data);
void	*routines(void *data);
void	create_philo_threads(t_session info);
void	join_all_threads(t_session info, t_philosopher monitor);
int		execute_1(t_philosopher *p, char *m, int mode);
void	alert_all_to_stop(t_session *s, int i);
int		check_number_of_meals(t_session *s);
int		simulation_must_stop(t_session *s);
void	update_last_meal_time(t_philosopher *p);
void	display_message(char *message, t_session *s, long value, int id);
void	update_meal_count(t_philosopher *p);
int		check_if_philo_started_eating(t_session *s, int i);
#endif