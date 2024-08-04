/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:51:55 by aohssine          #+#    #+#             */
/*   Updated: 2024/08/04 08:51:56 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/time.h>

#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define RESET    "\033[0m"

typedef pthread_mutex_t t_mtx ;
typedef struct s_forks t_fork ;
typedef struct s_philo t_philo ;

//////////////////////////////////////////////////////////
//                         INPUT                        //
//////////////////////////////////////////////////////////

typedef struct s_table{
    int num_philo ;
    int t_die;
    int t_eat;
    int t_sleep ;
    int meals ;
    size_t start_time;
    int stop_state;
    t_philo *philos;
    t_fork *forks;

    t_mtx *print;
    t_mtx *state;

}t_table;

//////////////////////////////////////////////////////////
//                    PHILOSPHER                        //
//////////////////////////////////////////////////////////

struct s_forks {
    t_mtx *fork;
    int id;
};

struct s_philo{
    int id;
    pthread_t thread;
    t_table *table;
    int die_state;
    size_t last_eat;
    long meals_counter;
    int right_fork;
    int left_fork;
} ;

//////////////////////////////////////////////////////////
//                        INPUT                         //
//////////////////////////////////////////////////////////

int	ft_atoi(const char *str);
int is_digit(char *str);
void parse_input(char **input);
void error_exit(const char* str);


//////////////////////////////////////////////////////////
//                    INIT DATA                         //
//////////////////////////////////////////////////////////

// void print_input(t_table*table);
void init_data(t_table *table, char **av);
void init_forks(t_table **table);
void assing_forks(t_table **table);
void    init_philos(t_table **table);

/* 
    start dinner
 */

void start_dinner(t_table *table);


//////////////////////////////////////////////////////////
//                       ROUTINE                        //
//////////////////////////////////////////////////////////

void my_usleep(long usec, t_philo *philo);
void *philos_routine(void *data);
int    think(t_philo *philo);
int    sleeep(t_philo *philo);
int    eat(t_philo **philo);

int    check_die(t_philo *philo);
// void died(t_philo *philo);

//////////////////////////////////////////////////////////
//                       UTILS                          //
//////////////////////////////////////////////////////////

size_t my_gettime(void);
void print_value(t_philo philo,char *mssg);

/* 
    GETTERS AND SETTERS 
*/
// size_t get_startTime(t_table table);

int get_state(t_table *table);
void set_state(t_table *table);

#endif