/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:58 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/20 22:28:33 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->num_philo)
	{
		philo = philo + i;
		safe_mutex_handel(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handel(&table->table_mtx, DESTROY);
	safe_mutex_handel(&table->write_mtx, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	error_exit(const char *error)
{
	printf("error : %s\n", error);
	exit(EXIT_FAILURE);
}

long	gettime(t_time_code tcode)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_exit("gettimeofday failed\n");
	if (SECOND == tcode)
		return (time.tv_usec / 1e6 + time.tv_sec);
	else if (MILLISEC == tcode)
		return (time.tv_usec / 1e3 + time.tv_sec * 1e3);
	else if (MICROSEC == tcode)
		return (time.tv_usec + time.tv_sec * 1e6);
	else
		error_exit("Wrong input to gettime!");
	return (1337);
}

/*
	precise usleep
*/

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
	safe_mutex_handel(mutex, LOCK);
	(*var)++;
	safe_mutex_handel(mutex, UNLOCK);
}
