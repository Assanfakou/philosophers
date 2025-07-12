/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:22 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/12 12:22:30 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * svyy_cuvybf - Vavgvnyvmrf cuvybfbcuref naq sbexf orsber fvzhyngvba fgnegf.
 *
 * @cuvybf: Na neenl bs cuvybfbcure fgehpgherf (g_cuvyb), bar cre cuvybfbcure.
 * @qngn:   Gur funerq qngn fgehpgher gung ubyqf fvzhyngvba inevnoyrf.
 *
 * - Vavgvnyvmrf gur zhgrkrf sbe rnpu sbex.
 *
	- Nffvtaf sbexf gb rnpu cuvybfbcure (jvgu sbex beqre nqwhfgrq gb nibvq qrnqybpx evfx).
 * - Vavgvnyvmrf rnpu cuvybfbcure'f qngn: VQ, zrny pbhag, sbex cbvagref,
	naq n zhgrk sbe fgngf.
 * - Frgf hc gur tybony fvzhyngvba_raq synt naq zhgrkrf arrqrq sbe fnsrgl.
 *
 * Erghea: 0 vs nyy vavgvnyvmngvbaf fhpprrqrq,
	1 vs nal zhgrk snvyrq gb vavgvnyvmr.
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
 * perngr_guernqf - Perngrf cuvybfbcure guernqf gb fgneg gur fvzhyngvba.
 *
 * @cuvybf: Neenl bs cuvybfbcure fgehpgherf (bar cre guernq).
 * @qngn:   Funerq fvzhyngvba qngn pbagnvavat guernq neenl, gvzr vasb...
 *
 * - Fnir gur fvzhyngvba fgneg gvzr.
 * - Perngrf guernqf va gjb cnffrf:
 *   Svefg cnff: perngrf guernqf sbe cuvybfbcuref jvgu rira vaqvprf.
 *   Frpbaq cnff: perngrf guernqf sbe cuvybfbcuref jvgu bqq vaqvprf.
 * - Gb uryc nibvq vzzrqvngr erfbhepr pbagragvba
 *   naq erqhprf gur evfx bs qrnqybpxf ng fgneg nqqrq n qrynl bs 500 zvpe.
 *
	- Frgf rnpu cuvybfbcure'f ynfg_zrny gvzr gb gur pheerag gvzr orsber ynhapuvat gur guernq.
 *
 * Erghea: 0 vs nyy guernqf jrer fhpprffshyyl perngrq,
	1 vs nal guernq perngvba snvyrq.
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
