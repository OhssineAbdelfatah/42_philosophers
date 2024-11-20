/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:07:15 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/18 01:51:36 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mtx);
	elapsed = gettime(MILLISEC) - philo->start_philo;
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-6ld %d DIED\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write_mtx);
}

long	gettime(t_time_code tcode)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	if (SECOND == tcode)
		return (time.tv_usec / 1e6 + time.tv_sec);
	else if (MILLISEC == tcode)
		return (time.tv_usec / 1e3 + time.tv_sec * 1e3);
	else if (MICROSEC == tcode)
		return (time.tv_usec + time.tv_sec * 1e6);
	else
		return (-1);
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
			usleep(200);
		else
		{
			while (gettime(MICROSEC) - start < usec)
				;
		}
	}
}

static bool	philo_died(t_philo *philo)
{
	long	time2die;
	long	elapsed;

	elapsed = 0;
	time2die = 0;
	if (get_bool(&philo->table->table_mtx, &philo->full))
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
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mtx, &(table->end_dinner), true);
				write_status(DIED, table->philos + i);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
