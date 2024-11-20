/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:06:57 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/18 01:48:37 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		set_bool(&philo->table->table_mtx, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*routine(void *data)
{
	t_philo	*this_philo;

	this_philo = (t_philo *)data;
	if (this_philo->id % 2 == 1)
	{
		write_status(SLEEPING, this_philo);
		my_usleep(this_philo->table->time2sleep, this_philo->table);
	}
	while (!simulation_finished(this_philo->table))
	{
		if (get_bool(&this_philo->philo_mutex, &this_philo->full))
			break ;
		write_status(THINKING, this_philo);
		eat(this_philo);
		write_status(SLEEPING, this_philo);
		my_usleep(this_philo->table->time2sleep, this_philo->table);
	}
	return (NULL);
}

void	*lone_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISEC));
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(100);
	return (NULL);
}

int	create_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i].last_meal_time = table->start_dinner ;
		table->philos[i].start_philo = table->start_dinner ;
		if (pthread_create(&table->philos[i].thread_id, NULL, routine,
				table->philos + i))
			return ((free(table->philos)), (free(table->forks)), 1);
		i++;
	}
	return (0);
}

int	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_meals == 0)
		return (1);
	table->start_dinner = gettime(MILLISEC);
	if (table->num_philo == 1)
	{
		table->philos[0].last_meal_time = table->start_dinner ;
		table->philos[i].start_philo = table->start_dinner ;
		if (pthread_create(&table->philos[0].thread_id, NULL, lone_routine,
				table->philos))
			return ((free(table->philos)), (free(table->forks)), 1);
	}
	else if (create_philos(table))
		return (1);
	if (pthread_create(&table->monitor, NULL, monitor_dinner, table))
		return ((free(table->philos)), (free(table->forks)), 1);
	i = -1;
	while (++i < table->num_philo)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mtx, &table->end_dinner, true);
	pthread_join(table->monitor, NULL);
	return (0);
}
