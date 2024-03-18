#include "philosophers.h"

int main(int argc, char **argv)
{
    session info;
    t_philosopher monitor;
    
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
