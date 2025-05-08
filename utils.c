/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:35:13 by hfakou            #+#    #+#             */
/*   Updated: 2025/05/05 12:02:58 by hfakou           ###   ########.fr       */
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
    if (data->philo_number > 200 || data->philo_number == 0)
        return (1);
    else if (data->time_t_die < 60 || data->time_t_eat < 80 || data->time_t_sleep < 60)
        return (1);
    else if (data->must_eat_times == 0)
        return (1);
    return (0);
}

int pars_data(t_data *data, char **av, int ac)
{
    int i;
    int j;

    j = ac;
    while(j > 0)
    {
        i = 0;
        while (av[j][i])
        {
            if (ft_isdigit(av[j][i]) == 1)
                return (1);
            i++;
        }
        j--;
    }
    data->philo_number = ft_atoi(av[1]);
    data->time_t_die = ft_atoi(av[2]);
    data->time_t_eat = ft_atoi(av[3]);
    data->time_t_sleep = ft_atoi(av[4]);
    if (ac == 5)
        data->must_eat_times = ft_atoi(av[5]);
    else
        data->must_eat_times = -1;
    if (check_max(data))
        return (1);
    return (0);
}

long long get_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_print_stat(t_philo *philo, char *action)
{
    if (philo->data->simulation_end)
        return ;
    printf("%lld %d %s\n", get_time_ms() - philo->data->start_time, philo->id, action);
}
int ft_atoi(char *str)
{
    int i;
    int signe;
    int res;

    i = 0;
    signe = 1;
    res  = 0;
    while (str[i] == 32 ||( str[i] >= 9 && str[i] <= 13))
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

