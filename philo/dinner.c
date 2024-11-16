/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:06 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/16 12:24:14 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	write_status(EATING, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISEC));
	my_usleep(philo->table->time2eat, philo->table);
	philo->meals_counter++;
	if (philo->table->nbr_meals > 0
		&& philo->meals_counter == philo->table->nbr_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*lone_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISEC));
	increase_long(&philo->table->table_mtx, &philo->table->thr_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*this_philo;

	this_philo = (t_philo *)data;
	wait_all_threads(this_philo->table);
	set_long(&this_philo->philo_mutex, &this_philo->last_meal_time,
		gettime(MILLISEC));
	increase_long(&this_philo->table->table_mtx,
		&this_philo->table->thr_running_nbr);
	if (this_philo->id % 2 == 0)
	{
		write_status(SLEEPING, this_philo);
		my_usleep(this_philo->table->time2sleep, this_philo->table);
	}
	while (!simulation_finished(this_philo->table))
	{
		if (get_bool(&this_philo->table->table_mtx, &this_philo->full))
			break ;
		thinking(this_philo);
		eat(this_philo);
		write_status(SLEEPING, this_philo);
		my_usleep(this_philo->table->time2sleep, this_philo->table);
	}
	return (NULL);
}

int	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_meals == 0)
		return 1;
	if (table->num_philo == 1){
		if(pthread_create(&table->philos[0].thread_id , NULL, lone_routine, table->philos))
			return ((free(table->philos)),(free(table->forks)), 1);
	}
	else
	{
		while (i < table->num_philo)
		{
			if(pthread_create(&table->philos[i].thread_id , NULL, routine, table->philos + i))
				return ((free(table->philos)),(free(table->forks)), 1);		
			i++;
		}
	}
	if(pthread_create(&table->monitor, NULL, monitor_dinner, table))
		return ((free(table->philos)),(free(table->forks)), 1);
	table->start_dinner = gettime(MILLISEC);
	set_bool(&table->table_mtx, &table->all_thr_ready, true);
	i = 0;
	while (i < table->num_philo)
	{
		// pthread_join(table->philos[i].thread_id, NULL);
		pthread_detach(table->philos[i].thread_id);
		// 	return ((free(table->philos)),(free(table->forks)), 1);
		i++;
	}
	set_bool(&table->table_mtx, &table->end_dinner, true);
	pthread_detach(table->monitor);
	return 0;
}
