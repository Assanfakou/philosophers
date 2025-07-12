/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:09:36 by usnxbh            #+#    #+#             */
/*   Updated: 2025/07/12 16:14:40 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 ** ft_usleep
	 Custom sleep function that checks simulation status while waiting.
 **
 ** @milliseconds: Duration to sleep, in milliseconds.

* @philo: Pointer to the philosopher structure (used to check simulation status).
 **
 ** This function simulates a sleep (delay) for the given number of milliseconds.
 ** Unlike the standard sleep, it:
 ** - Continuously checks if the simulation has ended (simulation_end == 1).
 ** - If the simulation ends during the wait, the function exits early.
 ** - Uses short usleep(500) intervals to stay responsive and avoid CPU overload.
 **
 ** Return: Always returns 0.
 */

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds)
	{
		pthread_mutex_lock(&philo->data->simulation);
		if (philo->data->simulation_end == 1)
		{
			pthread_mutex_unlock(&philo->data->simulation);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->simulation);
		usleep(500);
	}
	return (0);
}
/**
 ** philo_cycle - Executes one full action cycle for a philosopher.
 **
 ** @philo: Pointer to the philosopher's structure (t_philo).
 **
 ** This function simulates a single cycle of a philosopher:
 ** 1. Takes the left and right forks (using mutexes to lock them).
 ** 2. Prints actions: taking forks and eating.
 ** 3. Updates the last_meal time and meal count (protected by a mutex).
 ** 4. Sleeps for the eating duration.
 ** 5. Releases both forks.
 ** 6. Sleeps (simulating rest) and then thinks.
 **
 ** All shared resources (forks, stats) are protected by mutexes to avoid
 ** race conditions and ensure thread-safe updates and outputs.
 */

void	philo_cycle(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_stat(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->stats);
	ft_print_stat(philo, "has taken a fork");
	ft_print_stat(philo, "is eating");
	philo->num_meals++;
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->stats);
	ft_usleep(philo->data->time_t_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_print_stat(philo, "is sleeping");
	ft_usleep(philo->data->time_t_sleep, philo);
	ft_print_stat(philo, "is thinking");
}

/**
 ** routine - Main function executed by each philosopher thread.
 **
 ** @arg: A pointer to the philosopher's data (cast to void* for pthreads).
 **
 ** This function is the entry point for each thread. It handles:
 **
 *  - The special case when there is only one philosopher 
 *  (he takes one fork and dies).
 ** - An infinite loop where the philosopher performs actions (eat, sleep,
 *       	think).
 ** - A check at each loop to see if the simulation should end,
 *       using a shared flag.
 **
 ** The loop stops if:
 ** - The simulation_end flag is set (someone died or all ate enough).
 **
 ** Return: NULL when the thread ends.
 */

void	*routine(void *arg)
{
	t_philo	*philo;

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
