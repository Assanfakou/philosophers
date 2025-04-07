/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:35:13 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/07 12:54:54 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_data
{
    int philo_number;
    unsigned int time_t_die;
    unsigned int time_t_eat;
    unsigned int time_t_sleep;
    unsigned int count_philo_eat;
}   t_data;
typedef struct s_philo
{
    pthread_mutex_t *mutexes;
    pthread_t *th;
} t_philo;
