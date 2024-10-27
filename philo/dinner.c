/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:06 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/20 22:16:48 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handel(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handel(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISEC));
	philo->meals_counter++;
	write_status(EATING, philo);
	my_usleep(philo->table->time2eat, philo->table);
	if (philo->table->nbr_meals > 0
		&& philo->meals_counter == philo->table->nbr_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handel(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handel(&philo->second_fork->fork, UNLOCK);
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

void	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_meals == 0)
		return ;
	else if (table->num_philo == 1)
		safe_thread_handel(&table->philos[0].thread_id, lone_routine,
			table->philos, CREATE);
	else
		while (++i < table->num_philo)
			safe_thread_handel(&table->philos[i].thread_id, routine,
				&table->philos[i], CREATE);
	safe_thread_handel(&table->monitor, monitor_dinner, table, CREATE);
	table->start_dinner = gettime(MILLISEC);
	set_bool(&table->table_mtx, &table->all_thr_ready, true);
	i = -1;
	while (++i, table->num_philo)
		safe_thread_handel(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->end_dinner, true);
	safe_thread_handel(&table->monitor, NULL, NULL, JOIN);
}
