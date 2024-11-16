/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:15:02 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/16 12:06:28 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mtx);
	elapsed = gettime(MILLISEC) - get_long(&philo->table->table_mtx,
			&philo->table->start_dinner);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf("%-6ld %d has taken a fork\n", elapsed,
			philo->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-6ld %d DIED\n", elapsed,
			philo->id);
	pthread_mutex_unlock(&philo->table->write_mtx);
}

void	__error_exit(const char *error)
{
	(void)error;
	exit(EXIT_FAILURE);
}
