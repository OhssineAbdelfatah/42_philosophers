#include"philo.h"

size_t my_gettime(void)
{
    struct timeval  t_time;
    
    gettimeofday(&t_time, NULL);
    return t_time.tv_usec /1000  + t_time.tv_sec *  1000;

}