/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mon.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:14:03 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/02 11:47:02 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_philo *philo)
{
    if (get_time_ms() - philo->last_meal >= philo->data->time_t_die)
    {
        pthread_mutex_lock(&philo->data->simulation);
        philo->data->simulation_end = 1;
        pthread_mutex_unlock(&philo->data->simulation);
        printf("%lld %d is dead\n", get_time_ms() - philo->data->start_time, philo->id);
        return (1);
    }
    return (0);
}

void monitoring(t_philo *philo)
{
    int all_finished;
    int i;

    while (1)
    {
        i = 0;
        all_finished = 1;
        while (i < philo[0].data->philo_number)
        {
            if (check_death(&philo[i]))
                return ;
            if (philo->num_meals <= philo[0].data->must_eat_times)
                all_finished = 0;
            i++;
        }
        if (all_finished && philo->data->must_eat_times != -1)
        {
            pthread_mutex_lock(&philo->data->simulation);
            philo->data->simulation_end = 1;
            pthread_mutex_unlock(&philo->data->simulation);
            return ;
        }
    }
}

