#ifndef PHILO_H
#define PHILO_H

#include<unistd.h>
#include<stdio.h>
#include<pthread.h>


int	ft_atoi(const char *str);

typedef struct s_in{
    int num_philo ;
    int t_die;
    int t_eat;
    int t_sleep ;
    int meals ;
}t_in;

#endif