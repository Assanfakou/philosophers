/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:09:36 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/10 14:25:39 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t  start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds && philo->data->simulation_end == 0)
		usleep(500);
	return (0);
}

void philo_cycle(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork); // TAKE fork
	ft_print_stat(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork); // take fork
	pthread_mutex_lock(&philo->stats);
	ft_print_stat(philo, "has taken a fork");
	ft_print_stat(philo, "is eating");
	philo->num_meals++;
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->stats);
	ft_usleep(philo->data->time_t_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_print_stat(philo, "is sleeping ^^^");
	ft_usleep(philo->data->time_t_sleep, philo);
	ft_print_stat(philo, "is thinking ...");
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	if (philo->data->philo_number == 1)
	{
		ft_print_stat(philo, "has taken a fork");
		ft_usleep(philo->data->time_t_die, philo);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->simulation);
		if (philo->data->simulation_end != 0)
		{
			pthread_mutex_unlock(&philo->data->simulation);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->simulation);
		philo_cycle(philo);
	}
	return (NULL);
}
