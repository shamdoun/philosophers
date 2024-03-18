#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <libc.h>
struct cycle;
struct philo;

typedef struct cycle
{
    int nbr_philosophers;
    struct philo *all_philosophers;
    size_t start_time;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t max_num_meals;
    pthread_mutex_t display;
    pthread_mutex_t must_stop_lock;
    pthread_mutex_t meal_lock;
    pthread_mutex_t last_time_lock;
    int    must_stop;
} session;

typedef struct philo
{
    int id;
    session *s;
    size_t last_meal_time;
    size_t num_meals;
    pthread_t thread;
    pthread_mutex_t right_fork;
    pthread_mutex_t *left_fork;
} t_philosopher;

int	ft_atoi(const char *str);
void init(session *info, char **argv);
long gettime();
void *routines(void *data);
void *monitor_routine(void *data);
void *monitor_routine(void *data);
void *routines(void *data);
void create_philo_threads(session info);
void join_all_threads(session info, t_philosopher monitor);
int execute_1(t_philosopher *p, char *m, int mode);
void alert_all_to_stop(session *s, int i);
int check_number_of_meals(session *s);
int limit_reached(t_philosopher *p);
int simulation_must_stop(session *s);
void update_last_meal_time(t_philosopher *p);
void display_message(char *message, session *s, long value, int id);