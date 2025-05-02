#include "philo.h"

int end_semulation(t_philo_info *info)
{
    pthread_mutex_lock(&info->data->death_check);
    if (info->data->simulation_end)
    {
        pthread_mutex_unlock(&info->data->death_check);
        return (1);
    }
    pthread_mutex_unlock(&info->data->death_check);
    return (0);
}
int check_death(t_philo_info *info, t_data *data)
{
    // printf("last_meal :%lld, time_to_die: %d\n", info->last_meal, data->time_t_die);
    if (info->last_meal > data->time_t_die)
    {
        // printf("last_meal :%lld, time_to_die: %d\n", info->last_meal, data->time_t_die);
        if (end_semulation(info))
        {
            pthread_mutex_lock(&data->death_check);
            data->simulation_end = 1;
            pthread_mutex_unlock(&data->death_check);
            ft_print_stat(info, "died", get_time_ms() - data->start_time);
        }
        return (1);
    }
    return (0);
}

void monitoring(t_philo_info *philo)
{
    int i;
    t_data *data;
    int all_finished;

    data = philo->data;
    while (1)
    {
        i = 0;
        all_finished = 1;
        while (i < data->philo_number)
        {
            if (check_death(&philo[i], data))
            {
                // printf("DEBUG: Philosopher %d has died at %lld.\n", philo[i].id, get_time_ms() - philo->data->start_time);
                return ;
            }

            pthread_mutex_lock(&philo[i].meal_mutex);
            // printf("DEBUG: Philosopher %d meals: %d/%d\n", philo[i].id, philo[i].num_meals, data->count_philo_eat);
            if (philo->num_meals < data->count_philo_eat)
                all_finished = 0;
            pthread_mutex_unlock(&philo[i].meal_mutex);

            i++;
        }
        if (all_finished)
        {
            pthread_mutex_lock(&data->death_check);
            data->done_eating = 1;
            // printf("DEBUG: All philosophers have finished eating.\n");
            pthread_mutex_unlock(&data->death_check);
            return ;
        }
        // printf("DEBUG: Monitoring loop continuing...\n");
        usleep(1000);
    }
    return ;
}

