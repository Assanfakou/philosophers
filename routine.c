/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:09:36 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/02 16:35:11 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_usleep(size_t milliseconds, t_philo *philo)
{
        size_t  start;

        start = get_time_ms();
        while ((get_time_ms() - start) < milliseconds && philo->data->simulation_end == 0)
            usleep(500);
        return (0);
}
void manger(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
        ft_print_stat(philo, "has taken a fork");
        ft_print_stat(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
        ft_print_stat(philo, "has taken a fork");
        ft_print_stat(philo, "has taken a fork");
    }
    ft_print_stat(philo, "is eating");
}

void philo_cycle(t_philo *philo)
{
    manger(philo); 

    philo->num_meals++;
    philo->last_meal = get_time_ms();
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
