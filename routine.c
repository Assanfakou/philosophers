/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:09:36 by hfakou            #+#    #+#             */
/*   Updated: 2025/05/01 19:27:41 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void ft_eating_time(t_philo_info *info, long long now)
{
    if (info->id % 2 == 0)
    {
        pthread_mutex_lock(info->left_fork);
        now = get_time_ms() - info->data->start_time;
        ft_print_stat(info, "has taken a fork", now);
        pthread_mutex_lock(info->right_fork);
        now = get_time_ms() - info->data->start_time;
        ft_print_stat(info, "has taken a fork", now);
    }
    else
    {
        pthread_mutex_lock(info->right_fork);
        now = get_time_ms() - info->data->start_time;
        ft_print_stat(info, "has taken a fork", now);
        pthread_mutex_lock(info->left_fork);
        now = get_time_ms() - info->data->start_time;
        ft_print_stat(info, "has taken a fork", now);
    }
}

void *routine(void *args)
{
    t_philo_info *info = (t_philo_info *)args;
    long long last_meal_time = get_time_ms() - info->data->start_time;
    long long now;
    int currant_meals;
    info->last_meal = get_time_ms() - info->data->start_time;
    // usleep(1);
    
    while (1)
    {
        
        pthread_mutex_lock(&info->data->stop_mut);
        if (info->data->simulation_end)
        {
            pthread_mutex_unlock(&info->data->stop_mut);
            break;
        }
        pthread_mutex_unlock(&info->data->stop_mut);
        // usleep(50);
        pthread_mutex_lock(&info->data->stop_mut);
        if (info->data->count_philo_eat > 0 && currant_meals >= info->data->count_philo_eat)
        {
            // ft_print_stat(info, "finish", now);
            info->data->simulation_end = 1;
            pthread_mutex_unlock(&info->data->stop_mut);
            break;
        }
        pthread_mutex_unlock(&info->data->stop_mut);
        // if (now - last_meal_time > info->data->time_t_die)
        // {
        //     ft_print_stat(info, "died", now);
        //     pthread_mutex_lock(&info->data->stop_mut);
        //     info->data->simulation_end = 1;
        //     pthread_mutex_unlock(&info->data->stop_mut);
        //     break;
        // }
        ft_eating_time(info, now);
        now = get_time_ms() - info->data->start_time;
        
        // usleep(info->data->time_t_eat);
        pthread_mutex_lock(&info->meal_mutex);
        info->last_meal = get_time_ms() - info->data->start_time;
        pthread_mutex_unlock(&info->meal_mutex);
        ft_print_stat(info, "is eating", now);
        usleep(info->data->time_t_eat * 1000);
        
        pthread_mutex_lock(&info->meal_mutex);
        info->num_meals++;
        currant_meals = info->num_meals;
        pthread_mutex_unlock(&info->meal_mutex);
        
        pthread_mutex_unlock(info->left_fork);
        pthread_mutex_unlock(info->right_fork);
        now = get_time_ms() - info->data->start_time;
        ft_print_stat(info, "is sleeping", now);
        usleep(info->data->time_t_sleep * 1000);
        now = get_time_ms() - info->data->start_time;
        ft_print_stat(info, "is thinking", now);
    }
    return (NULL);
}
