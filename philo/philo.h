#ifndef PHILO_H
#define PHILO_H

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
 #include <sys/time.h>


int	ft_atoi(const char *str);

typedef struct s_in{
    int num_philo ;
    int t_die;
    int t_eat;
    int t_sleep ;
    int meals ;
    pthread_mutex_t *print;
}t_in;

typedef struct s_philo{
    pthread_t *thread;
    t_in *input;
    int last_eat;
    int id;
} t_philo;

void print_input(t_in in);
int is_digit(char *str);
int parse_input(char **input ,t_in *in ,int ac);
int philo(t_in *in);

void *philos_routine(void *data);
int    think(t_philo *philo);



#endif