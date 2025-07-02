/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:22 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/02 16:05:50 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int fill_philos(t_philo *philos, t_data *data)
{
    int i;

    data->simulation_end = 0;
    i = 0;
    while (i < data->philo_number)
        if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
            return (1);
    i = 0;
    while (i < data->philo_number)
    {
        philos[i].id = i + 1;
        philos[i].num_meals = 0;
        philos[i].left_fork = &(data->forks[i]);
        philos[i].right_fork = &(data->forks[(i + 1) % data->philo_number]);
        philos[i].data = data;
        if (pthread_mutex_init(&data->simulation, NULL) != 0)
            return (1);
        if (pthread_mutex_init(&data->num_meals, NULL) != 0)
            return (1);
        i++;
    }
    return (0);
}

int create_threads(t_philo *philos, t_data *data)
{
    int i;
    
    i = 0;
    data->start_time = get_time_ms();
    while (i < data->philo_number)
    {
        philos[i].last_meal = get_time_ms();
        if (pthread_create(&data->threads[i], NULL, &routine, &philos[i]) != 0)
            return (1);
        i++;
    }
    return (0);
}

void cleaning(t_data *data)
{
    int j;

    j = 0;
    while (j < data->philo_number)
    {
        pthread_detach(data->threads[j]);
        j++;
    }

    j = 0;
    while (j < data->philo_number)
    {
        pthread_mutex_destroy(&data->forks[j]);
        j++;
    }
}

int main(int ac, char **av)
{
    t_data shared_data;
    t_philo philos[MAX_NUMBER];


    if (ac != 6 && ac != 5)
        return (1);
    if (pars_data(&shared_data, av, ac - 1))
    {
        printf("Error in Parse Data\n");
        return (2);
    }
    if (fill_philos(philos, &shared_data) == 1)
    {
        printf("Error While fill philos");
        return (3);
    }
    if (create_threads(philos, &shared_data) == 1)
    {
        printf("Error in creat thread");
        return (4);
    }
    monitoring(philos);
    cleaning(&shared_data);
}
