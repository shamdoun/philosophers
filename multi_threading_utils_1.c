#include "philosophers.h"


void alert_all_to_stop(session *s, int i)
{
    pthread_mutex_unlock(&s->last_time_lock);
    pthread_mutex_lock(&s->must_stop_lock);
    s->must_stop = 1;
    pthread_mutex_unlock(&s->must_stop_lock);
    pthread_mutex_lock(&s->display);
    printf("%ld %d died\n", gettime(s) - s->start_time, s->all_philosophers[i].id);
    pthread_mutex_unlock(&s->display);
}

int check_number_of_meals(session *s)
{
    size_t sum;
    int i;

    i = 0;
    sum = 0;
    pthread_mutex_lock(&s->meal_lock);
    while (s->max_num_meals && i < s->nbr_philosophers)
    {
        sum += s->all_philosophers[i].num_meals;
        i++;
    }
    if (s->max_num_meals && sum == s->max_num_meals * s->nbr_philosophers)
    {
        s->must_stop = 1;
        pthread_mutex_unlock(&s->meal_lock);
        return (1);
    }
    pthread_mutex_unlock(&s->meal_lock);
    return (0);
}

int simulation_must_stop(session *s)
{
    pthread_mutex_lock(&s->must_stop_lock);
    if (s->must_stop)
    {
        pthread_mutex_unlock(&s->must_stop_lock);
        return (1);
    }
    pthread_mutex_unlock(&s->must_stop_lock);
    return (0);
}

void update_last_meal_time(t_philosopher *p)
{
    pthread_mutex_lock(&p->s->last_time_lock);
    p->last_meal_time = gettime(p->s);
    pthread_mutex_unlock(&p->s->last_time_lock);
}
