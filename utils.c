/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:35:13 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/23 12:30:34 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (0);
    return (1);
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
    return (0);
}

void ft_mutex(t_philo_info *info, char *msg, long long time, pthread_mutex_t mutex)
{
        // for the mutexes declaration
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
int fill_info(t_philo_info *info, t_philo *thds, t_data *data)
{
    int i_info;
    int i;

    i = 0;
    thds->mutexes = malloc(sizeof(pthread_mutex_t) * data->philo_number);
    while (i < data->philo_number)
    {
        if (pthread_mutex_init(&thds->mutexes[i], NULL) != 0)
            return (1);
        i++;
    }
    i_info = 0;
    thds->th = malloc(sizeof(pthread_t) * data->philo_number);
    while (i_info < data->philo_number)
    {
        info[i_info].id = i_info;
        info[i_info].state = 0;
        info[i_info].left_fork = thds->mutexes;
        info[i_info].left_fork = &(thds->mutexes[i_info]);
        info[i_info].right_fork = &thds->mutexes[(i_info + 1) % data->philo_number];
        info[i_info].data = data;
        info[i_info].num_meals = 0;
        if (pthread_mutex_init(&info[i_info].meal_mutex, NULL) != 0)
            return (1);        
        i_info++;
    }
    return (0);
}

int creat_threads(t_philo *thds, t_philo_info *info)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < info->data->philo_number)
    {
        if (pthread_create(&thds->th[i], NULL, &routine, &info[i]) != 0)
            return (1);
        i++;
    }
    while (j < info->data->philo_number)
    {
        if (pthread_join(thds->th[j], NULL) != 0)
            return (1);
        j++;
    }
    return (0);
}

