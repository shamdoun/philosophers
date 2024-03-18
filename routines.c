#include "philosophers.h"

static int philo_eats(t_philosopher *p)
{
    if(!execute_1(p, "%ld %d took left fork\n", 1))
        return (1);
    if(!execute_1(p, "%ld %d took right fork\n", 2))
    {
        pthread_mutex_unlock(p->left_fork);
        return (1);
    }
    if(!execute_1(p, "%ld %d is eating\n", 5))
    {
        pthread_mutex_unlock(p->left_fork);
        pthread_mutex_unlock(&p->right_fork);
        return (1);
    }
    pthread_mutex_unlock(p->left_fork);
    pthread_mutex_unlock(&p->right_fork);
    return (0);
}

static void *special_case(t_philosopher *p)
{
    if(!execute_1(p, "%ld %d took right fork\n", 2))
        return (NULL);
    usleep(p->s->time_to_die * 1000);
    return (NULL);
}

void *monitor_routine(void *data)
{
    int     i;
    session *s;
    size_t  time;

    i = 0;
    s = (session *)data;
    while (1)
    {
            i  = 0;
            time = gettime(s);
            while (i < s->nbr_philosophers)
            {
                pthread_mutex_lock(&s->last_time_lock);
                if (time - s->all_philosophers[i].last_meal_time >= s->time_to_die)
                {
                    alert_all_to_stop(s, i);
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

void *routines(void *data)
{
    t_philosopher *p;

    p = (t_philosopher *)data;
    if (p->id % 2 == 0)
        usleep(15000);
    if (p->s->nbr_philosophers == 1)
        return(special_case(p));
    while (!simulation_must_stop(p->s))
    {
        if (philo_eats(p))
            break ;
        if(!execute_1(p, "%ld %d is sleeping\n", 3))
            break ;
        if(!execute_1(p, "%ld %d is thinking\n", 4))
            break ;
    }
    return (NULL);
}
