#include "philo.h"

void pars_data(t_philo_info *data, char **av, int size)
{
    int i = 0;

    while (i < size)
    {
        data[i].data.philo_number = atoi(av[1]);
        data[i].data.time_t_die = atoi(av[2]) * 1000;
        data[i].data.time_t_eat = atoi(av[3]) * 1000;
        data[i].data.time_t_sleep = atoi(av[4]) * 1000;
        data[i].data.count_philo_eat = atoi(av[5]);    
        i++;
    }
}
void handle_state_philo(t_philo_info *info)
{
    if (info->state == 0)
    {
        printf("%ld %d is eating\n",info->data.time_t_eat, info->id);
        // usleep(info->data.time_t_eat);
        info->state = 1;
        // printf("%d, %ld, %ld, %ld, %ld\n", info->data.philo_number, info->data.time_t_die, info->data.time_t_eat, info->data.time_t_sleep, info->data.count_philo_eat);

    }
}
void *func(void *args)
{
    int i = gettid();
    t_philo_info *arg = (t_philo_info *) args; 
    handle_state_philo(arg);
    // printf("treaeds id :[%d]\n", i);
    // if (arg->id == 0)
    //     printf("thread 0\n");
    // else if (arg->id == 1)
    //     printf("thread 1\n");
    // else if (arg->id == 2)
    //     printf("thread 2\n");
    // else if (arg->id == 3)
    //     printf("tread 3\n");
    // printf("hello from threads\n");
    pthread_exit(NULL);
}

int main(int ac, char **av)
{
    int i = 0;  
    t_philo thds;
    int num_philo = atoi(av[1]);
    
    if (ac != 6)
        return (1);
    t_philo_info info[num_philo];
    pars_data(info, av, num_philo);
    // memset(info, '0', info->data.philo_number);
    int i_info = 0;
    while (i_info < info->data.philo_number)
    {
        info[i_info].id = i_info;
        info[i_info].state = 0;
        info[i_info].left_fork = thds.mutexes;
        info[i_info].time_t_eatt = 1000;
        i_info++;
    }
    
    thds.mutexes = malloc(sizeof(pthread_mutex_t) * info->data.philo_number);
    while (i < info->data.philo_number)
    {
        if (pthread_mutex_init(&thds.mutexes[i], NULL) != 0)
            return (2);
        i++;
    }
    thds.th = malloc(sizeof(pthread_t) * info->data.philo_number);
    i = 0;
    while (i < info->data.philo_number)
    {
        if (pthread_create(&thds.th[i], NULL, &func, &info[i]) != 0)
            return (3);

        if (pthread_join(thds.th[i], NULL) != 0)
            return (4);
            i++;
    }
    free(thds.mutexes);
    printf("%d, %ld, %ld, %ld, %ld", info->data.philo_number, info->data.time_t_die, info->data.time_t_eat, info->data.time_t_sleep, info->data.count_philo_eat);

    // pthread_create(&t1, NULL, &action, i + 1);
    // pthread_join(t1, NULL);
    // pthread_create(&t2, NULL, &action, NULL);
    // pthread_join(t2, NULL);
    // pthread_create(&t3, NULL, &action, NULL);
    // pthread_join(t3, NULL); 
    // pthread_create(&t4, NULL, &action, NULL);
    // pthread_join(t4, NULL);

}