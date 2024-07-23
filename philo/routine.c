#include"philo.h"

void *philos_routine(void *data)
{
    t_philo *this_philo;

    this_philo = (t_philo *)data;
    //  think sleep eat
    if(this_philo->id %2 == 0)
        sleeep(this_philo);
    while(!this_philo->die_state)
    {
        eat(&this_philo);
        sleeep(this_philo);
    }
    return NULL;
}

int    think(t_philo *philo)
{
    pthread_mutex_lock(philo->table->print);
    printf(BOLD_RED"%zu"RESET" %d is thinking\n",my_gettime() - philo->table->start_time,philo->id);
    pthread_mutex_unlock(philo->table->print);
    return 0;
}

int    eat(t_philo **philo)
{
    if(!(*philo)->die_state){
        think(*philo);
        pthread_mutex_lock((*philo)->table->forks[(*philo)->right_fork].fork);
            pthread_mutex_lock((*philo)->table->print);
            printf(BOLD_RED"%zu"RESET" %d has taken a fork\n",my_gettime()- (*philo)->table->start_time ,(*philo)->id);
            pthread_mutex_unlock((*philo)->table->print);
        
            pthread_mutex_lock((*philo)->table->forks[(*philo)->left_fork].fork);
                pthread_mutex_lock((*philo)->table->print);
                printf(BOLD_RED"%zu"RESET" %d has taken a fork\n",my_gettime()- (*philo)->table->start_time,(*philo)->id);
                printf(BOLD_RED"%zu"RESET" %d is eating\n",my_gettime() - (*philo)->table->start_time,(*philo)->id);
                pthread_mutex_unlock((*philo)->table->print);        

            pthread_mutex_unlock((*philo)->table->forks[(*philo)->left_fork].fork);

        pthread_mutex_unlock((*philo)->table->forks[(*philo)->right_fork].fork);

        (*philo)->last_eat = my_gettime() - (*philo)->table->start_time;
        check_die(philo);
        my_usleep((*philo)->table->t_eat *1000);
    }
    return 0;
    
}

void died(t_philo *philo)
{
    my_usleep(philo->table->t_die * 1000);
    pthread_mutex_lock(philo->table->print);
            printf(BOLD_RED"%zu"RESET" %d has died\n",my_gettime()- philo->table->start_time ,philo->id);
    pthread_mutex_unlock(philo->table->print);
}

int    sleeep(t_philo *philo)
{   
    if(!philo->die_state){
        pthread_mutex_lock(philo->table->print);
        printf(BOLD_RED"%zu"RESET" %d is sleeping\n",my_gettime()- philo->table->start_time,philo->id);
        pthread_mutex_unlock(philo->table->print);
        check_die(&philo);
        my_usleep(philo->table->t_sleep *1000);
    }
    return 0;
}

void check_die(t_philo **this_philo)
{   
    pthread_mutex_lock((*this_philo)->table->state);
    if((my_gettime() - (*this_philo)->last_eat) > (size_t)((*this_philo)->table->t_die)){
        (*this_philo)->table->stop_state += 1;
        (*this_philo)->die_state = 1;
        if((*this_philo)->table->stop_state == 1)
            died(*this_philo);
    }
    pthread_mutex_unlock((*this_philo)->table->state);

}

void my_usleep(long usec)
 {
    struct timeval start, current;
    long elapsed;
    long rem;

    gettimeofday(&start, NULL);
    gettimeofday(&current, NULL);
    elapsed = (current.tv_sec - start.tv_sec) * 1000000L + (current.tv_usec - start.tv_usec);
    rem = usec - elapsed;

    if (rem > 1000) 
        usleep(rem / 2);
    while (elapsed < usec){
        gettimeofday(&current, NULL);
        elapsed = (current.tv_sec - start.tv_sec) * 1000000L + (current.tv_usec - start.tv_usec);
        rem = usec - elapsed;

        if (rem > 1000) 
            usleep(rem / 2);
    }
}
