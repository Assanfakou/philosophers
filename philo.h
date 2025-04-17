/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assankou <assankou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:35:13 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/16 18:38:20 by assankou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_data
{
    int philo_number;
    unsigned long int time_t_die;
    unsigned long int time_t_eat;
    unsigned long int time_t_sleep;
    unsigned long int count_philo_eat;
}   t_data;
typedef struct s_philo
{
    pthread_mutex_t *mutexes;
    pthread_t *th;
} t_philo;

typedef struct s_philo_info
{
    int id;
    int state;
    int num_meals;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    t_data data;
}  t_philo_info;