/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:35:13 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/18 18:44:55 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void pars_data(t_data *data, char **av, int size)
{
    data->time_t_die = atoi(av[2]);
    data->philo_number = atoi(av[1]);
    data->time_t_eat = atoi(av[3]);
    data->time_t_sleep = atoi(av[4]);
    data->count_philo_eat = atoi(av[5]) * data->philo_number;
}
long long get_time_ms(t_data *data)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time;
}