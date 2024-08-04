/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:50:07 by aohssine          #+#    #+#             */
/*   Updated: 2024/08/04 09:16:17 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void *philos_routine(void *data)
{
    t_philo *this_philo;

    this_philo = (t_philo *)data;
    //  think sleep eat
    if(this_philo->id %2 == 0)
        think(this_philo);
    while(get_state(((this_philo)->table)) == 0)
    {
        eat(&this_philo);
        if(get_state(((this_philo)->table)) != 0)
            break;
        sleeep(this_philo);
        if(get_state(((this_philo)->table)) != 0)
            break;
    }
    return NULL;
}

int    think(t_philo *philo)
{
    print_value(*philo, "is thinking");
    return 0;
}

int    eat(t_philo **philo)
{
    if( get_state(((*philo)->table)) == 0)
    {
        think(*philo);
        pthread_mutex_lock((*philo)->table->forks[(*philo)->right_fork].fork);
            print_value(**philo, "has taken a fork");
            pthread_mutex_lock((*philo)->table->forks[(*philo)->left_fork].fork);
                print_value(**philo, "has taken a fork");
                print_value(**philo, "is eating");   
                (*philo)->last_eat = my_gettime() - (*philo)->table->start_time;
                my_usleep((*philo)->table->t_eat *1000, *philo);
                (*philo)->meals_counter += 1; 
            pthread_mutex_unlock((*philo)->table->forks[(*philo)->left_fork].fork);
        pthread_mutex_unlock((*philo)->table->forks[(*philo)->right_fork].fork);
    }
    return 0;
    
}

int    sleeep(t_philo *philo)
{   
    if( get_state((philo->table))  == 0)
    {
        print_value(*philo, "is sleeping");   
        my_usleep(philo->table->t_sleep *1000, philo);
    }
    return 0;
}

/*
    chceck if the thread is dead outside the child thread in main
*/
// void died(t_philo *philo)
// {
//     my_usleep(philo->table->t_die * 1000);
//     pthread_mutex_lock(philo->table->print);
//             printf(BOLD_RED"%zu"RESET" %d has died\n",my_gettime()- philo->table->start_time ,philo->id);
//     pthread_mutex_unlock(philo->table->print);
//     return ;
// }
int check_die(t_philo *this_philo)
{   
    if((my_gettime() - this_philo->table->start_time - this_philo->last_eat) > (size_t)(this_philo->table->t_die))
    {
        set_state(this_philo->table);
        print_value(*this_philo, BOLD_RED"has died"RESET);
        return 0;
    }
    return 1;
}

/*
    hard coded my_usleep
*/

void my_usleep(long usec, t_philo *philo)
{
    size_t now;

    now = my_gettime();
    while (my_gettime() - now < (size_t)usec ){
        usleep(100);
        if( check_die(philo) == 0 || get_state((philo->table)) != 0 )
            return ;
    }
    return;
}

// void my_usleep(long usec, t_philo *philo)
// {
//     struct timeval start, current;
//     long elapsed;
//     long rem;

//     if(check_die(philo) == 0 || get_state((philo->table)) != 0)
//         return ;
//     gettimeofday(&start, NULL);
//     gettimeofday(&current, NULL);
//     elapsed = (current.tv_sec - start.tv_sec) * 1000000L + (current.tv_usec - start.tv_usec);
//     rem = usec - elapsed;

//     if (rem > 1000) 
//         usleep(rem / 2);
//     while (elapsed < usec)
//     {
//         if(check_die(philo) == 0 || get_state((philo->table)) != 0)
//             return ;
//         gettimeofday(&current, NULL);
//         elapsed = (current.tv_sec - start.tv_sec) * 1000000L + (current.tv_usec - start.tv_usec);
//         rem = usec - elapsed;

//         if (rem > 1000) 
//             usleep(rem / 2);
//     }
// }
