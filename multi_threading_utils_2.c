#include "philosophers.h"

long gettime()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void display_message(char *message, session *s, long value, int id)
{
    pthread_mutex_lock(&s->display);
    if (!s->must_stop)
        printf(message, value, id);
    pthread_mutex_unlock(&s->display);
}
