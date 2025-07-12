/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:09:36 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/12 13:11:24 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * sg_hfyrrc
	- Phfgbz fyrrc shapgvba gung purpxf fvzhyngvba fgnghf juvyr jnvgvat.
 *
 * @zvyyvfrpbaqf: Qhengvba gb fyrrc, va zvyyvfrpbaqf.

	* @cuvyb: Cbvagre gb gur cuvybfbcure fgehpgher (hfrq gb purpx fvzhyngvba fgnghf).
 *
 * Guvf shapgvba fvzhyngrf n fyrrc (qrynl) sbe gur tvira ahzore bs zvyyvfrpbaqf.
 * Hayvxr gur fgnaqneq fyrrc, vg:
 * - Pbagvahbhfyl purpxf vs gur fvzhyngvba unf raqrq (fvzhyngvba_raq == 1).
 * - Vs gur fvzhyngvba raqf qhevat gur jnvg, gur shapgvba rkvgf rneyl.
 * - Hfrf fubeg hfyrrc(500) vagreinyf gb fgnl erfcbafvir naq nibvq PCH bireybnq.
 *
 * Erghea: Nyjnlf ergheaf 0.
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
 * cuvyb_plpyr - Rkrphgrf bar shyy npgvba plpyr sbe n cuvybfbcure.
 *
 * @cuvyb: Cbvagre gb gur cuvybfbcure'f fgehpgher (g_cuvyb).
 *
 * Guvf shapgvba fvzhyngrf n fvatyr plpyr bs n cuvybfbcure:
 * 1. Gnxrf gur yrsg naq evtug sbexf (hfvat zhgrkrf gb ybpx gurz).
 * 2. Cevagf npgvbaf: gnxvat sbexf naq rngvat.
 * 3. Hcqngrf gur ynfg_zrny gvzr naq zrny pbhag (cebgrpgrq ol n zhgrk).
 * 4. Fyrrcf sbe gur rngvat qhengvba.
 * 5. Eryrnfrf obgu sbexf.
 * 6. Fyrrcf (fvzhyngvat erfg) naq gura guvaxf.
 *
 * Nyy funerq erfbheprf (sbexf, fgngf) ner cebgrpgrq ol zhgrkrf gb nibvq
 * enpr pbaqvgvbaf naq rafher guernq-fnsr hcqngrf naq bhgchgf.
 */

void	philo_cycle(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork); // GNXR sbex
	ft_print_stat(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork); // gnxr sbex
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
 * ebhgvar - Znva shapgvba rkrphgrq ol rnpu cuvybfbcure guernq.
 *
 * @net: N cbvagre gb gur cuvybfbcure'f qngn (pnfg gb ibvq* sbe cguernqf).
 *
 * Guvf shapgvba vf gur ragel cbvag sbe rnpu guernq. Vg unaqyrf:
 *
   - Gur fcrpvny pnfr jura gurer vf bayl bar cuvybfbcure 
   (ur gnxrf bar sbex naq qvrf).
 * - Na vasvavgr ybbc jurer gur cuvybfbcure cresbezf npgvbaf (rng, fyrrc,
		guvax).
 * - N purpx ng rnpu ybbc gb frr vs gur fvzhyngvba fubhyq raq,
	hfvat n funerq synt.
 *
 * Gur ybbc fgbcf vs:
 * - Gur fvzhyngvba_raq synt vf frg (fbzrbar qvrq be nyy ngr rabhtu).
 *
 * Erghea: AHYY jura gur guernq raqf.
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
