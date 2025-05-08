/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:09:36 by hfakou            #+#    #+#             */
/*   Updated: 2025/05/05 15:13:08 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void ft_wait(int time_to_wait, t_philo *philo)
// {
//     if (philo->data->simulation_end)
//         return;
    
//     while (time_to_wait >= 500000)
//     {
//         if (philo->data->simulation_end)
//             return ;
//         usleep(500000);
//         time_to_wait -= 500000;
//     }
//     if (time_to_wait > 0)
//         usleep(time_to_wait);
// }

int     ft_usleep(size_t milliseconds, t_philo *philo)
{
        size_t  start;

        start = get_time_ms();
        while ((get_time_ms() - start) < milliseconds && philo->data->simulation_end == 0)
                usleep(500);
        return (0);
}

void philo_cycle(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
        ft_print_stat(philo, "has taken a fork");
        ft_print_stat(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
        ft_print_stat(philo, "has taken a fork");
        ft_print_stat(philo, "has taken a fork");
    }
    philo->num_meals++;
    philo->last_meal = get_time_ms();
    ft_print_stat(philo, "is eating");
    ft_usleep(philo->data->time_t_eat, philo);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    ft_print_stat(philo, "is sleeping");
    ft_usleep(philo->data->time_t_sleep, philo);
    ft_print_stat(philo, "is thinking");
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = arg;
    if (philo->data->philo_number == 1)
    {
        ft_print_stat(philo, "has taken a fork");
        ft_usleep(philo->data->time_t_die, philo);
        return (NULL);
    }
    while (philo->data->simulation_end == 0)
       philo_cycle(philo);
    return (NULL);
}
