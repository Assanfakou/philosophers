#include "philo.h"

void *routine(void *args)
{
    t_philo_info *info = (t_philo_info *)args;
    long long last_meal_time = get_time_ms(info->data);
    long long now;
    int currant_meals;
    
    while (1)
    {
        pthread_mutex_lock(&info->data->stop_mut);
        if (info->data->simulation_end)
        {
            pthread_mutex_unlock(&info->data->stop_mut);
            break;
        }
        pthread_mutex_unlock(&info->data->stop_mut);
        if (info->data->count_philo_eat > 0 && currant_meals >= info->data->count_philo_eat)
        {
            ft_print_stat(info, "finish", now);
            pthread_mutex_lock(&info->data->stop_mut);
            info->data->simulation_end = 1;
            pthread_mutex_unlock(&info->data->stop_mut);
            break;
        }
        pthread_mutex_lock(&info->meal_mutex);
        info->num_meals++;
        currant_meals = info->num_meals;
        pthread_mutex_unlock(&info->meal_mutex);
        now = get_time_ms(info->data);
        if (now - last_meal_time > info->data->time_t_die)
        {
            ft_print_stat(info, "died", now);
            pthread_mutex_lock(&info->data->stop_mut);
            info->data->simulation_end = 1;
            pthread_mutex_unlock(&info->data->stop_mut);
            break;
        }
        ft_print_stat(info, "is thinking", now);
        info->state = 1;
        if (info->id % 2 == 0)
        {
            pthread_mutex_lock(info->left_fork);
            ft_print_stat(info, "took left fork", now);
            pthread_mutex_lock(info->right_fork);
            ft_print_stat(info, "took right fork", now);
            info->state = 2;
        }
        else
        {
            pthread_mutex_lock(info->right_fork);
            ft_print_stat(info, "else took right fork", now);
            pthread_mutex_lock(info->left_fork);
            ft_print_stat(info, "else took left fork", now);
            info->state = 2;
        }
        last_meal_time = get_time_ms(info->data);
        ft_print_stat(info, "is eating", now);
        usleep(info->data->time_t_eat * 1000);
        
        pthread_mutex_unlock(info->left_fork);
        pthread_mutex_unlock(info->right_fork);

        ft_print_stat(info, "is sleeping", now);
        usleep(info->data->time_t_sleep * 1000);
        if (info->state == 2)
            info->state = 0;
    }
    return (NULL);
}
