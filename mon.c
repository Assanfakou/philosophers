/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mon.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:14:03 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/13 17:04:02 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philos)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < philos->data->philo_number)
	{
		philo = &philos[i];
		pthread_mutex_lock(&philo->stats);
		if (get_time_ms() - philo->last_meal > philos->data->time_t_die)
		{
			pthread_mutex_lock(&philos->data->simulation);
			philos->data->simulation_end = 1;
			pthread_mutex_unlock(&philos->data->simulation);
			printf("%s%lld %d is dead\n", RED, get_time_ms()
					- philos->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->stats);
			return (1);
		}
		pthread_mutex_unlock(&philo->stats);
		i++;
	}
	return (0);
}

int	all_philos_full(t_philo *philos)
{
	int	all_finished;
	int	i;

	all_finished = 0;
	i = 0;
	while (i < philos->data->philo_number)
	{
		pthread_mutex_lock(&philos[i].stats);
		if (philos[i].num_meals >= philos->data->must_eat_times)
			all_finished++;
		pthread_mutex_unlock(&philos[i].stats);
		i++;
	}
	if (all_finished >= philos->data->philo_number)
	{
		pthread_mutex_lock(&philos->data->simulation);
		philos->data->simulation_end = 1;
		pthread_mutex_unlock(&philos->data->simulation);
		return (1);
	}
	return (0);
}

void	monitoring(t_philo *philos)
{
	while (1)
	{
		if (check_death(philos))
			return ;
		if (philos->data->must_eat_times < 0)
			continue ;
		if (all_philos_full(philos))
			return ;
/*
		usleep(500);
*/
	}
}
