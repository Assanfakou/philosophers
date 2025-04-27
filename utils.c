/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:35:13 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/27 12:32:57 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (0);
    return (1);
}

int check_max(t_data *data)
{
    if (data->philo_number > 200)
        return (1);
    else if (data->time_t_die < 60 || data->time_t_eat < 60 || data->time_t_sleep < 60)
        return (1);
    return (0); 
}

int pars_data(t_data *data, char **av, int ac)
{
    int i;

    while(ac > 0)
    {
        i = 0;
        while (av[ac][i])
        {
            if (ft_isdigit(av[ac][i]) == 1 && av[ac][i] != '\0')
                return (1);
            i++;
        }
        ac--;
    }
    data->philo_number = ft_atoi(av[1]);
    data->time_t_die = ft_atoi(av[2]);
    data->time_t_eat = ft_atoi(av[3]);
    data->time_t_sleep = ft_atoi(av[4]);
    data->count_philo_eat = ft_atoi(av[5]);
    if (check_max(data))
        return (1);
    return (0);
}

long long get_time_ms(t_data *data)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time;
}

void ft_print_stat(t_philo_info *info, char *stat, long long time)
{
    pthread_mutex_lock(&info->data->print_mut);
    printf("%lld %d %s\n", time, info->id, stat);
    pthread_mutex_unlock(&info->data->print_mut);
}
int ft_atoi(char *str)
{
    int i;
    int signe;
    int res;

    i = 0;
    signe = 1;
    res  = 0;
    while (str[i] == 32 || str[i] >= 9 && str[i] <= 13)
        i++;
    if (str[i] == '+' || str[1] == '-')
    {
        if (str[i] == '-')
            signe = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res * signe);
}


