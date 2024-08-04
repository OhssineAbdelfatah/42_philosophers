/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:52:04 by aohssine          #+#    #+#             */
/*   Updated: 2024/08/04 08:52:05 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

size_t my_gettime(void)
{
    struct timeval  t_time;
    
    gettimeofday(&t_time, NULL);
    return t_time.tv_usec /1000  + t_time.tv_sec *  1000;

}

void print_value(t_philo philo,char *mssg)
{
    pthread_mutex_lock(philo.table->print);
    printf(BOLD_RED"%zu"RESET" %d %s\n",my_gettime()- philo.table->start_time ,philo.id , mssg);
    pthread_mutex_unlock(philo.table->print);
}
/* 
    setters
 */
void set_state(t_table *table)
{
    pthread_mutex_lock(table->state);
    table->stop_state = 1;
    pthread_mutex_unlock(table->state);
}

// void set_meal(t_philo *philo)
// {
//     pthread_mutex_lock(table->state);
//     table->stop_state = 1;
//     pthread_mutex_unlock(table->state);
// }

/*  
    getters
*/

int get_state(t_table *table)
{
    int i ;
    pthread_mutex_lock(table->state);
    i = table->stop_state;
    pthread_mutex_unlock(table->state);
    return i;
}
// size_t get_startTime(t_table *table)
// {
//     size_t i ;
//     pthread_mutex_lock(table.state);
//     i = table.start_time;
//     pthread_mutex_unlock(table.state);
//     return i;
// }