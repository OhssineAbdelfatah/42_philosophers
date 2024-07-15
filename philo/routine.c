#include"philo.h"

// int cycle_of_life(void *input)
// {
//     t_in *in ;
//     in = (t_in *)input;
//     think();
//     eat(in->t_eat);
//     sleeep(in->t_sleep);
//     return 0;
// }

int    think(t_philo *philo)
{
    unsigned long time;
    my_gettime(&time);
    time = time - philo->input->start_time ; 
    pthread_mutex_lock((philo->print));
    printf("[%lu]: %d is thinking\n",time,philo->id);
    pthread_mutex_unlock((philo->print));
    return 0;
}

int    eat(t_philo *philo)
{
    
}

int    sleeep(t_philo *philo){

    unsigned long time;
    my_gettime(&time);
    time = time - philo->input->start_time ;
    pthread_mutex_lock((philo->print));
    printf("[%lu]: %d is sleeping\n",time,philo->id);
    pthread_mutex_unlock((philo->print));
    pthread_mutex_lock((philo->sleep));
    usleep(philo->input->t_sleep);
    pthread_mutex_unlock((philo->sleep));
    return 0;
}
