/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:22 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/12 16:05:06 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * fill_philos - Initializes philosophers and forks before simulation starts.
 *
 * @philos: An array of philosopher structures (t_philo), one per philosopher.
 * @data:   The shared data structure that holds simulation variables.
 *
 * - Initializes the mutexes for each fork.
 *
	- Assigns forks to each philosopher (with fork order adjusted to avoid deadlock risk).
 * - Initializes each philosopher's data: ID, meal count, fork pointers,
	and a mutex for stats.
 * - Sets up the global simulation_end flag and mutexes needed for safety.
 *
 * Return: 0 if all initializations succeeded,
	1 if any mutex failed to initialize.
 */
int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->simulation_end = 0;
	while (i < data->philo_number)
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
			return (1);
	if (pthread_mutex_init(&data->simulation, NULL) != 0)
		return (1);
	return (0);
}

int	fill_philos(t_philo *philos, t_data *data)
{
	int	i;

	if (init_mutex(data))
		return (1);
	i = 0;
	while (i < data->philo_number)
	{
		philos[i].id = i + 1;
		philos[i].num_meals = 0;
		if (i % 2 == 0)
		{
			philos[i].left_fork = &(data->forks[i]);
			philos[i].right_fork = &(data->forks[(i + 1) % data->philo_number]);
		}
		else
		{
			philos[i].right_fork = &(data->forks[i]);
			philos[i].left_fork = &(data->forks[(i + 1) % data->philo_number]);
		}
		philos[i].data = data;
		if (pthread_mutex_init(&philos[i].stats, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * create_threads - Creates philosopher threads to start the simulation.
 *
 * @philos: Array of philosopher structures (one per thread).
 * @data:   Shared simulation data containing thread array, time info...
 *
 * - Save the simulation start time.
 * - Creates threads in two passes:
 *   First pass: creates threads for philosophers with even indices.
 *   Second pass: creates threads for philosophers with odd indices.
 * - To help avoid immediate resource contention
 *   and reduces the risk of deadlocks at start added a delay of 500 micr.
 *
	- Sets each philosopher's last_meal time to the current time before launching the thread.
 *
 * Return: 0 if all threads were successfully created,
	1 if any thread creation failed.
 */

int	create_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_ms();
	while (i < data->philo_number)
	{
		philos[i].last_meal = get_time_ms();
		if (pthread_create(&data->threads[i], NULL, &routine, &philos[i]) != 0)
			return (1);
		i += 2;
	}
	usleep(500);
	i = 1;
	while (i < data->philo_number)
	{
		philos[i].last_meal = get_time_ms();
		if (pthread_create(&data->threads[i], NULL, &routine, &philos[i]) != 0)
			return (1);
		i += 2;
	}
	return (0);
}

void	cleaning(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->philo_number)
	{
		pthread_join(data->threads[j], NULL);
		j++;
	}
	j = 0;
	while (j < data->philo_number)
	{
		pthread_mutex_destroy(&data->forks[j]);
		j++;
	}
	pthread_mutex_destroy(&data->simulation);
}

int	main(int ac, char **av)
{
	t_data	shared_data;
	t_philo	philos[MAX_NUMBER];

	if (ac != 6 && ac != 5)
	{
		printf("%sthe input should be : number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
				RED);
		return (1);
	}
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
