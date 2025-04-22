/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:22 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/22 14:52:18 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    int i = 0;  
    t_philo thds;
    int num_philo = atoi(av[1]);
    t_philo_info info[num_philo];
    t_data shared_data;
    int i_info = 0;
    
    if (ac != 6)
        return (1);
    pars_data(&shared_data, av, num_philo);
    shared_data.simulation_end = 0;
    pthread_mutex_init(&shared_data.stop_mut, NULL);
    pthread_mutex_init(&shared_data.print_mut, NULL);
    
    thds.mutexes = malloc(sizeof(pthread_mutex_t) * shared_data.philo_number);
    while (i < shared_data.philo_number)
    {
        if (pthread_mutex_init(&thds.mutexes[i], NULL) != 0)
            return (2);
        i++;
    }
    thds.th = malloc(sizeof(pthread_t) * shared_data.philo_number);
    while (i_info < shared_data.philo_number)
    {
        info[i_info].id = i_info;
        info[i_info].state = 0;
        info[i_info].left_fork = thds.mutexes;
        info[i_info].left_fork = &(thds.mutexes[i_info]);
        info[i_info].right_fork = &thds.mutexes[(i_info + 1) % num_philo];
        info[i_info].data = &shared_data;
        info[i_info].num_meals = 0;
        if (pthread_mutex_init(&info[i_info].meal_mutex, NULL) != 0)
            return (3);        
        i_info++;
    }
    i = 0;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    shared_data.start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    while (i < shared_data.philo_number)
    {
        if (pthread_create(&thds.th[i], NULL, &routine, &info[i]) != 0)
            return (3);
        i++;
    }
    int j = 0;
    while (j < shared_data.philo_number)
    {
        if (pthread_join(thds.th[j], NULL) != 0)
            return (4);
        j++;
    }
    free(thds.mutexes);
}
