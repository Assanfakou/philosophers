/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:35:13 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/22 11:15:38 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void pars_data(t_data *data, char **av, int size)
{
    data->philo_number = atoi(av[1]);
    data->time_t_die = atoi(av[2]);
    data->time_t_eat = atoi(av[3]);
    data->time_t_sleep = atoi(av[4]);
    data->count_philo_eat = atoi(av[5]);
}
long long get_time_ms(t_data *data)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time;
}
void ft_mutex(t_philo_info *info, char *msg, long long time, pthread_mutex_t mutex)
{
        // mutexes
}
void ft_print_stat(t_philo_info *info, char *stat, long long time)
{
    pthread_mutex_lock(&info->data->print_mut);
    printf("%lld %d %s\n", time, info->id, stat);
    pthread_mutex_unlock(&info->data->print_mut);
}