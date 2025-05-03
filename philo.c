/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:22 by hfakou            #+#    #+#             */
/*   Updated: 2025/05/03 18:09:26 by hfakou           ###   ########.fr       */
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
void ft_errour(char *str)
{
    write(2, str, ft_strlen(str));
}
void cleaning(t_data *data)
{
    int j;

    j = 0;
    while (j < data->philo_number)
    {
        pthread_join(data->threads[j], NULL);
        j++;
    }

    j = 0;
    while (j < data->philo_number)
    {
        pthread_mutex_destroy(data->forks + j);
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
        ft_errour("Error in Parse Data\n");
        return (1);
    }
    if (fill_philos(philos, &shared_data) == 1)
    {
        ft_errour("Error While fill philos");
        return (21);
    }
    if (create_threads(philos, &shared_data) == 1)
    {
        ft_errour("Error in creat thread");
        return (17);
    }
    monitoring(philos);
    cleaning(&shared_data);
}
