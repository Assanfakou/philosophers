/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:35:13 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/10 14:23:41 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_NUMBER 200

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YLW "\e[0;33m"

typedef struct s_data
{
	int				philo_number;
	int				time_t_die;
	int				time_t_eat;
	int				time_t_sleep;
	int				must_eat_times;
	long long		start_time;
	int				simulation_end;
	pthread_t		threads[MAX_NUMBER];
	pthread_mutex_t	forks[MAX_NUMBER];
	pthread_mutex_t	simulation;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				num_meals;
	time_t			last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	stats;
	t_data			*data;
}					t_philo;

int					pars_data(t_data *data, char **av, int ac);
long long			get_time_ms(void);
void				ft_print_stat(t_philo *philo, char *action);
void				*routine(void *args);
int					ft_atoi(char *str);
int					ft_isdigit(char c);

int					fill_philos(t_philo *philos, t_data *data);
int					create_threads(t_philo *philos, t_data *data);
int					check_max(t_data *data);

void				monitoring(t_philo *philo);

int					ft_strlen(char *str);
