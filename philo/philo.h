#ifndef PHILO_H
#define PHILO_H

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/time.h>

//////////////////////////////////////////////////////////
//                         INPUT                        //
//////////////////////////////////////////////////////////

typedef struct s_in{
    int num_philo ;
    int t_die;
    int t_eat;
    int t_sleep ;
    int meals ;
    long start_time;
}t_in;

//////////////////////////////////////////////////////////
//                    PHILOSPHER                        //
//////////////////////////////////////////////////////////

typedef struct s_philo{
    pthread_t thread;
    pthread_mutex_t *sleep;
    pthread_mutex_t *print;
    t_in *input;
    int last_eat;
    long meals_counter;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    int id;
} t_philo;

//////////////////////////////////////////////////////////
//                        INPUT                         //
//////////////////////////////////////////////////////////

int	ft_atoi(const char *str);
int is_digit(char *str);
int parse_input(char **input ,t_in *in ,int ac);

//////////////////////////////////////////////////////////
//                        PHILO                         //
//////////////////////////////////////////////////////////

void print_input(t_in in);
int philo(t_in *in);
void *philos_routine(void *data);

//////////////////////////////////////////////////////////
//                       ROUTINE                        //
//////////////////////////////////////////////////////////

int    think(t_philo *philo);
int    sleeep(t_philo *philo);

#endif