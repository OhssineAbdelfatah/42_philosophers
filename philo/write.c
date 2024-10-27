/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:15:02 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/20 22:26:52 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	if (philo->full)
		return ;
	safe_mutex_handel(&philo->table->write_mtx, LOCK);
	elapsed = gettime(MILLISEC) - get_long(&philo->table->table_mtx,
			&philo->table->start_dinner);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf(GREEN "%-6ld" RESET " %d has taken a fork\n", elapsed,
			philo->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(GREEN "%-6ld" RESET " %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(GREEN "%-6ld" RESET " %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(GREEN "%-6ld" RESET " %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(GREEN "%-6ld" RESET " %d " RED "DIED" RESET "\n", elapsed,
			philo->id);
	safe_mutex_handel(&philo->table->write_mtx, UNLOCK);
}
