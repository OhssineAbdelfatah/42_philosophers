/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:09 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/16 12:23:22 by aohssine         ###   ########.fr       */
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

static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_philo)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		if(pthread_mutex_init(&philo->philo_mutex, NULL))
			return 1; 
		assing_forks(philo, table->forks, i);
		i++;
	}
	return 0;
}

int	data_init(t_table *table)
{
	int	i;

	table->all_thr_ready = false;
	table->end_dinner = false;
	table->thr_running_nbr = 0;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philo);
	if(!(table->philos))
		return (1);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_philo);
	if(!(table->forks))
		return ((free(table->philos)), 1);
	if(pthread_mutex_init(&table->table_mtx, NULL))
		return ((free(table->philos)),(free(table->forks)), 1); // free abatal
	if(pthread_mutex_init(&table->write_mtx, NULL))
		return ((free(table->philos)),(free(table->forks)), 1); // free abatal
	i = 0;
	while (i < table->num_philo)
	{
		if(pthread_mutex_init(&table->forks[i].fork, NULL))
			return ((free(table->philos)),(free(table->forks)), 1);
		table->forks[i].fork_id = i;
		i++;
	}
	if(philo_init(table))
		return ((free(table->philos)),(free(table->forks)), 1);
	return 0;
}

void ff(){
	system("leaks philo");
}

int	main(int ac, char **av)
{
	// atexit(ff);
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if(init_table(&table, av))
			return 0;
		if(data_init(&table))
			return 0;
		if(start_dinner(&table))
			return 0;
		clean(&table);
	}
	else{
		printf("wrong input\n");
		return 0;
	}
	return (0);
}
