#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data {
    int philo_count;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int max_meals;
    long long start_time;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    int sim_ended;
} t_data;

typedef struct s_philo {
    int id;
    int meals_eaten;
    long long last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
} t_philo;

long long get_time_ms(t_data *data) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time;
}

void print_status(t_philo *philo, char *status) {
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%lld %d %s\n", get_time_ms(philo->data), philo->id, status);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void *philosopher(void *arg) {
    t_philo *philo = (t_philo *)arg;
    
    while (1) {
        // Think
        print_status(philo, "is thinking");
        
        // Pick up forks
        if (philo->id % 2 == 0) {
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken left fork");
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken right fork");
        } else {
            usleep(100);
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken right fork");
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken left fork");
        }
        
        // Eat
        philo->last_meal = get_time_ms(philo->data);
        print_status(philo, "is eating");
        usleep(philo->data->time_to_eat * 1000);
        philo->meals_eaten++;
        
        // Put down forks
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        
        // Sleep
        print_status(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
        
        // Check if done
        if (philo->data->max_meals > 0 && philo->meals_eaten >= philo->data->max_meals)
            break;
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 5 && argc != 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [max_meals]\n", argv[0]);
        return 1;
    }

    t_data data;
    data.philo_count = atoi(argv[1]);
    data.time_to_die = atoi(argv[2]);
    data.time_to_eat = atoi(argv[3]);
    data.time_to_sleep = atoi(argv[4]);
    data.max_meals = (argc == 6) ? atoi(argv[5]) : -1;
    data.sim_ended = 0;

    // Initialize time
    struct timeval tv;
    gettimeofday(&tv, NULL);
    data.start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

    // Initialize mutexes
    pthread_mutex_init(&data.print_mutex, NULL);
    data.forks = malloc(sizeof(pthread_mutex_t) * data.philo_count);
    for (int i = 0; i < data.philo_count; i++) {
        pthread_mutex_init(&data.forks[i], NULL);
    }

    // Create philosophers
    t_philo *philos = malloc(sizeof(t_philo) * data.philo_count);
    pthread_t *threads = malloc(sizeof(pthread_t) * data.philo_count);

    for (int i = 0; i < data.philo_count; i++) {
        philos[i].id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].last_meal = 0;
        philos[i].left_fork = &data.forks[i];
        philos[i].right_fork = &data.forks[(i + 1) % data.philo_count];
        philos[i].data = &data;
        pthread_create(&threads[i], NULL, philosopher, &philos[i]);
    }

    // Wait for threads
    for (int i = 0; i < data.philo_count; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < data.philo_count; i++) {
        pthread_mutex_destroy(&data.forks[i]);
    }
    pthread_mutex_destroy(&data.print_mutex);
    free(data.forks);
    free(philos);
    free(threads);

    return 0;
}