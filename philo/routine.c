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
    struct timeval time;
    gettimeofday(&time,NULL);
    pthread_mutex_lock((philo->print));
    printf("[%d]: %d is thinking\n",time.tv_usec,philo->id);
    pthread_mutex_unlock((philo->print));
    return 0;
}

/* int    eat(int time){

} */

int    sleeep(t_philo *philo){

    struct timeval time;
    gettimeofday(&time,NULL);
    pthread_mutex_lock((philo->print));
    printf("[%d]: %d is sleeping\n",time.tv_usec,philo->id);
    pthread_mutex_unlock((philo->print));
    pthread_mutex_lock((philo->sleep));
    usleep(philo->input->t_sleep);
    pthread_mutex_unlock((philo->sleep));
    return 0;
}
