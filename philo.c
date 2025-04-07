#include "philo.h"

// void *action(void *i)
// {
//     if (i == 1)
//         printf("philo eat 1\n");
//     else if (i == 2)
//         printf("philo eat 2\n");
//     else if (i == 3)
//         printf("philo eat 3\n");
//     else if (i == 4)
//         printf("philo eat 4\n");   
//     sleep(2);
//     printf("philo think\n");
// };

void pars_data(t_data *data, char **av)
{
    data->philo_number = atoi(av[1]);
    data->time_t_die = atoi(av[2]);
    data->time_t_eat = atoi(av[3]);
    data->time_t_sleep = atoi(av[4]);
    data->count_philo_eat = atoi(av[5]);
}
void *func()
{
    printf("hello from threads\n");
    sleep(1); 
}

int main(int ac, char **av)
{
    int i = 0;  
    
    t_data data;
    t_philo thds;

    if (ac != 6)
        return (1);
    pars_data(&data, av);
    thds.mutexes = malloc(sizeof(pthread_mutex_t) * data.philo_number);
    while (i < data.philo_number)
    {
        if (pthread_mutex_init(&thds.mutexes[i], NULL) != 0)
            return (2);
        i++;
    }
    thds.th = malloc(sizeof(pthread_t) * data.philo_number);
    i = 0;
    while (i < data.philo_number)
    {
        if (pthread_create(&thds.th[i], NULL, &func, NULL) != 0)
            return (3);
        if (pthread_join(thds.th[i], NULL) != 0)
            return (4);
        i++;
    }
    free(thds.mutexes);
    // printf("%d, %d, %d, %d, %d", data.philo_number, data.time_t_die, data.time_t_eat, data.time_t_sleep, data.count_philo_eat);

    // pthread_create(&t1, NULL, &action, i + 1);
    // pthread_join(t1, NULL);
    // pthread_create(&t2, NULL, &action, NULL);
    // pthread_join(t2, NULL);
    // pthread_create(&t3, NULL, &action, NULL);
    // pthread_join(t3, NULL); 
    // pthread_create(&t4, NULL, &action, NULL);
    // pthread_join(t4, NULL);

}
