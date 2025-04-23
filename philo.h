/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:35:13 by hfakou            #+#    #+#             */
/*   Updated: 2025/04/23 12:29:59 by hfakou           ###   ########.fr       */
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
    int time_t_die;
    int time_t_eat;
    int time_t_sleep;
    int count_philo_eat;
    long long start_time;

    int simulation_end; 
    pthread_mutex_t stop_mut;
    pthread_mutex_t print_mut;
    
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
    t_data *data;
    pthread_mutex_t meal_mutex;
}  t_philo_info;

int pars_data(t_data *data, char **av, int ac);
long long get_time_ms(t_data *data);
void ft_print_stat(t_philo_info *info, char *stat, long long time);
void *routine(void *args);
int ft_atoi(char *str);
int ft_isdigit(char c);

int fill_info(t_philo_info *info, t_philo *thds, t_data *data);
int creat_threads(t_philo *thds, t_philo_info *info);