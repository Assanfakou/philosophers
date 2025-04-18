/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:22 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/18 19:17:36 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
    t_philo_info *info = (t_philo_info *)args;
    long long last_meal_time = get_time_ms(info->data);
    long long now;
    int currant_meals=0;
    
    while (1)
    {
        pthread_mutex_lock(&info->data->stop_mut);
        if (info->data->simulation_end)
        {
            pthread_mutex_unlock(&info->data->stop_mut);
            break;
        }
        pthread_mutex_unlock(&info->data->stop_mut);
        pthread_mutex_lock(&info->meal_mutex);
        info->num_meals++;
        currant_meals = info->num_meals;
        pthread_mutex_unlock(&info->meal_mutex);
        if (info->data->count_philo_eat > 0 && currant_meals >= info->data->count_philo_eat)
        {
            printf("%lld %d finish eating\n", now, info->id);
            pthread_mutex_lock(&info->data->stop_mut);
            info->data->simulation_end = 1;
            pthread_mutex_unlock(&info->data->stop_mut);
            break;
        }
        now = get_time_ms(info->data);
        if (now - last_meal_time > info->data->time_t_die)
        {
            printf("%lld %d died\n", now, info->id);
            pthread_mutex_lock(&info->data->stop_mut);
            info->data->simulation_end = 1;
            pthread_mutex_unlock(&info->data->stop_mut);
            break;
        }       
        printf("%lld %d is thinking\n", now, info->id);
        info->state = 1;
        if (info->id % 2 == 0)
        {
            pthread_mutex_lock(info->left_fork);
            printf("%lld %d took left fork\n", now, info->id);
            pthread_mutex_lock(info->right_fork);
            printf("%lld %d took right fork\n", now, info->id);
            info->state = 2;
        }
        else
        {
            pthread_mutex_lock(info->right_fork);
            printf("%lld %d right fork locked\n", now, info->id);
            pthread_mutex_lock(info->left_fork);
            printf("%lld %d left fork locked\n", now, info->id);
            info->state = 2;
        }
        last_meal_time = get_time_ms(info->data);

        printf("%lld %d is eating\n", now, info->id);
        usleep(info->data->time_t_eat * 1000);

        pthread_mutex_unlock(info->left_fork);
        pthread_mutex_unlock(info->right_fork);

        printf("%lld %d is sleeping\n", now, info->id);
        usleep(info->data->time_t_sleep * 1000);
    }
    return (NULL);
}
int main(int ac, char **av)
{
    int i = 0;  
    t_philo thds;
    int num_philo = atoi(av[1]);
    t_philo_info info[num_philo];
    t_data shared_data;
    struct timeval tv;
    int i_info = 0;
    
    if (ac != 6)
        return (1);
    pars_data(&shared_data, av, num_philo);
    shared_data.simulation_end = 0;
    pthread_mutex_init(&shared_data.stop_mut, NULL);
    gettimeofday(&tv, NULL);
    
    thds.mutexes = malloc(sizeof(pthread_mutex_t) * shared_data.philo_number);
    while (i < shared_data.philo_number)
    {
        if (pthread_mutex_init(&thds.mutexes[i], NULL) != 0)
        return (2);
        i++;
    }
    shared_data.start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    thds.th = malloc(sizeof(pthread_t) * shared_data.philo_number);
    while (i_info < shared_data.philo_number)
    {
        info[i_info].id = i_info;
        info[i_info].state = 0;
        info[i_info].left_fork = thds.mutexes;
        info[i_info].left_fork = &(thds.mutexes[i_info]);
        info[i_info].right_fork = &thds.mutexes[(i_info + 1) % num_philo];
        info[i_info].data = &shared_data;
        info[i_info].num_meals = 0;
        i_info++;
    }
    for (int s = 0; i < num_philo; s++) {
    if (pthread_mutex_init(&thds.mutexes[s], NULL) != 0) {
        printf("Error: Fork mutex %d init failed\n", i);
        exit(1);
    }
}
if (pthread_mutex_init(&shared_data.stop_mut, NULL) != 0) {
    printf("Error: Stop mutex init failed\n");
    exit(1);
}
    i = 0;
    while (i < shared_data.philo_number)
    {
        if (pthread_create(&thds.th[i], NULL, &routine, &info[i]) != 0)
        return (3);

        if (pthread_join(thds.th[i], NULL) != 0)
            return (4);
            i++;
    }
    free(thds.mutexes);
}
