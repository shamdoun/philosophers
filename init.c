#include "philosophers.h"

static void init_forks(session *info)
{
    int i;

    i = 0;
    while (i < info->nbr_philosophers)
    {
        pthread_mutex_init(&info->all_philosophers[i].right_fork, NULL);
        i++;
    }
    i = 0;
    while (i < info->nbr_philosophers)
    {
        info->all_philosophers[i].id = i + 1;
        info->all_philosophers[i].s = info;
        if (i)
        {
            info->all_philosophers[i].left_fork = &info->all_philosophers[i - 1].right_fork;
        }
        if (i == info->nbr_philosophers - 1)
        {
            info->all_philosophers[0].left_fork = &info->all_philosophers[i].right_fork;
        }
        i++;
    }  
}

static void init_mutexes(session *info)
{
    if(pthread_mutex_init(&info->display, NULL))
        exit(1);
    if(pthread_mutex_init(&info->must_stop_lock, NULL))
        exit(1);
    if(pthread_mutex_init(&info->last_time_lock, NULL))
        exit(1);
    if(pthread_mutex_init(&info->meal_lock, NULL))
        exit(1);
}

void init(session *info, char **argv)
{
    info->nbr_philosophers = ft_atoi(argv[1]);
    if (!info->nbr_philosophers)
        exit(1);
    info->time_to_die = ft_atoi(argv[2]);
    info->time_to_eat = ft_atoi(argv[3]); 
    info->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        info->max_num_meals = ft_atoi(argv[5]);
    else
        info->max_num_meals = -1;
    info->must_stop = 0;
    info->start_time = gettime();
    init_mutexes(info);
    info->all_philosophers = malloc(sizeof(t_philosopher) * info->nbr_philosophers);
    if (!info->all_philosophers)
        exit(1);
    init_forks(info);
}
