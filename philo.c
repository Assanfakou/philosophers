/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:22 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/23 12:30:24 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
        return (2);
    shared_data.simulation_end = 0;
    pthread_mutex_init(&shared_data.stop_mut, NULL);
    pthread_mutex_init(&shared_data.print_mut, NULL);
    
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
