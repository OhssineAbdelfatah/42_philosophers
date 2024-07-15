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
    pthread_mutex_lock(philo->input->print);
    gettimeofday(&time,NULL);
    printf(" %d is thinking",philo->id);
    pthread_mutex_unlock(philo->input->print);
    return 0;
}

/* int    eat(int time){

}

int    sleeep(int time){

} */