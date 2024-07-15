#include"philo.h"

void my_gettime(unsigned long *time)
{
    struct timeval  t_time;
    
    gettimeofday(&t_time, NULL);
    *time = t_time.tv_usec + t_time.tv_sec * 1000;

    return NULL;
}