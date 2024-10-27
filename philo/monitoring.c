/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:22 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/20 22:22:02 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time2die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISEC) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time2die = philo->table->time2die / 1000;
	if (elapsed > time2die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mtx, &table->thr_running_nbr,
			table->num_philo))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->num_philo)
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mtx, &(table->end_dinner), true);
				write_status(DIED, table->philos + i);
				break ;
			}
		}
	}
	return (NULL);
}
