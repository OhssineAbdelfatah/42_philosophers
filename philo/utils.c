/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:58 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/16 11:44:42 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_table *table)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = 0;
	while (i < table->num_philo)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
		i++;
	}
	i = 0 ;
	while (i < table->num_philo)
	{
		fork = table->forks + i;
		pthread_mutex_destroy(&fork->fork);
		i++;
	}
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->write_mtx);
	// safe_mutex_handel(&table->table_mtx, DESTROY);
	// safe_mutex_handel(&table->write_mtx, DESTROY);
	free(table->forks);
	free(table->philos);
}

long	gettime(t_time_code tcode)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return -1;
	if (SECOND == tcode)
		return (time.tv_usec / 1e6 + time.tv_sec);
	else if (MILLISEC == tcode)
		return (time.tv_usec / 1e3 + time.tv_sec * 1e3);
	else if (MICROSEC == tcode)
		return (time.tv_usec + time.tv_sec * 1e6);
	else
		return -1;
	return (1337);
}

void	my_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSEC);
	while (gettime(MICROSEC) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSEC);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(100);
		else
		{
			while (gettime(MICROSEC) - start < usec)
				;
		}
	}
}

void	increase_long(t_mtx *mutex, long *var)
{
	pthread_mutex_lock(mutex);
	(*var)++;
	pthread_mutex_unlock(mutex);
}
