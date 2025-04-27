/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:22 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/27 13:08:42 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int fill_info(t_philo_info *info, t_philo *thds, t_data *data)
{
    int i_info;
    
    i_info = 0;
    if (creat_threads(thds, info))
        return (1);
    thds->th = malloc(sizeof(pthread_t) * data->philo_number);
    while (i_info < data->philo_number)
    {
        info[i_info].id = i_info + 1;
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
void ft_errour(char *str)
{
    write(2, str, ft_strlen(str));
}

int ft_mutex(t_philo *thds, t_philo_info *filo)
{
    int i;
    
    i = 0;
    thds->mutexes = malloc(sizeof(pthread_mutex_t) * filo->data->philo_number);
    while (i < filo->data->philo_number)
    {
        if (pthread_mutex_init(&thds->mutexes[i], NULL) != 0)
            return (1);
        i++;
    }
    if (pthread_mutex_init(&filo->data->stop_mut, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&filo->data->print_mut, NULL) != 0)
        return (1);
    return (0);
}

int main(int ac, char **av)
{
    int i = 0;  
    t_philo thds;
    int num_philo = ft_atoi(av[1]);
    t_philo_info info[num_philo];
    t_data shared_data;
    int i_info = 0;
    
    if (ac != 6)
        return (1);
    
    if (pars_data(&shared_data, av, ac - 1))
    {
        ft_errour("Error in Parse Data\n");
        return (1);
    }
    shared_data.simulation_end = 0;
    
    if (fill_info(info, &thds, &shared_data) == 1)
        return (21);
    i = 0;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    shared_data.start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    if (creat_threads(&thds, info) == 1)
        return (17);
    free(thds.mutexes);
}
