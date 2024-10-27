/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:16 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/20 22:19:02 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assing_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->num_philo;
	philo->first_fork = &forks[i];
	philo->second_fork = &forks[(i + 1) % philo_nbr];
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_philo)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handel(&philo->philo_mutex, INIT);
		assing_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	table->all_thr_ready = false;
	table->end_dinner = false;
	table->thr_running_nbr = 0;
	table->philos = (t_philo *)safe_malloc(sizeof(t_philo) * table->num_philo);
	table->forks = (t_fork *)safe_malloc(sizeof(t_fork) * table->num_philo);
	safe_mutex_handel(&table->table_mtx, INIT);
	safe_mutex_handel(&table->write_mtx, INIT);
	i = -1;
	while (++i < table->num_philo)
	{
		safe_mutex_handel(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
