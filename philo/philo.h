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

typedef struct s_philo{
    pthread_t thread;
    int last_eat;
} t_philo;
int is_digit(char *str);
int parse_input(char **input ,t_in *in ,int ac);
int philo(t_in in);

int philo(t_in in);
void *philos_routine(void *data);



#endif