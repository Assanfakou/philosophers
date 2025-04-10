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

/*
                ## OUTLINE ##
        ** handle the philo to eat **
    ** 1- philosofers sits next to each other every philo has a plate of spaguetee
        and a fork in the right of there hands so N of Philo and N forks and N plates
    ** 2- So the project is that every philo is a thread has to eat in a spessific amount of time that the user 
        give us, but the problem is the philo has to eat with two forks the one that is n his left and right one,
        while the philo is eating the one that sits beside him he won't get access to the his right fork.
           --Philo eating blocks the resources with mutex, if the time is done the philo has to unlock the resourses to the othe
            philo and then change his state to sleep then the same goes to the next one sits next of him
     


    ** 1- every philosopher has to eat but when it can be 
        
    
*/
void handle_state_philo(t_philo_info *info)
{
    if (info->state == 0 && info->left_fork)
    {
        printf("%ld %d is eating\n",info->data.time_t_eat, info->id);
        // usleep(info->data.time_t_eat);
        info->state = 1;
    }
    if (info->state == 1)
        printf("%ld %d i sleeping\n", info->data.time_t_sleep, info->id);
}
void *routine(void *args)
{
    int i = gettid();
    t_philo_info *arg = (t_philo_info *) args; 
    handle_state_philo(arg);
    usleep(arg->data.time_t_eat);
    printf("treaeds id :[%d]\n", i);
    pthread_exit(NULL);
    return (NULL);
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
    
    thds.mutexes = malloc(sizeof(pthread_mutex_t) * info->data.philo_number);
    while (i < info->data.philo_number)
    {
        if (pthread_mutex_init(&thds.mutexes[i], NULL) != 0)
        return (2);
        i++;
    }
    thds.th = malloc(sizeof(pthread_t) * info->data.philo_number);
    int i_info = 0;
    while (i_info < info->data.philo_number)
    {
        info[i_info].id = i_info;
        info[i_info].state = 0;
        info[i_info].left_fork = thds.mutexes;
        info[i_info].time_t_eatt = 1000;
        info[i_info].left_fork = &(thds.mutexes[i_info]);
        info[i_info].right_fork = &thds.mutexes[(i_info + 1) % num_philo];
        i_info++;
    }
    i = 0;
    while (i < info->data.philo_number)
    {
        if (pthread_create(&thds.th[i], NULL, &routine, &info[i]) != 0)
            return (3);

        if (pthread_join(thds.th[i], NULL) != 0)
            return (4);
            i++;
    }
    free(thds.mutexes);
    // printf("%d, %ld, %ld, %ld, %ld", info->data.philo_number, info->data.time_t_die, info->data.time_t_eat, info->data.time_t_sleep, info->data.count_philo_eat);

    // pthread_create(&t1, NULL, &action, i + 1);
    // pthread_join(t1, NULL);
    // pthread_create(&t2, NULL, &action, NULL);
    // pthread_join(t2, NULL);
    // pthread_create(&t3, NULL, &action, NULL);
    // pthread_join(t3, NULL); 
    // pthread_create(&t4, NULL, &action, NULL);
    // pthread_join(t4, NULL);

}