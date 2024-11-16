/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:37 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/16 12:05:20 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_thr_ready))
		;
}

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_number)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_number)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}
