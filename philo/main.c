/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:09 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/20 23:30:19 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		init_table(&table, av);
		data_init(&table);
		start_dinner(&table);
		clean(&table);
	}
	else
	{
		error_exit("wrong input\n ./philo number_philos\
			time_die time_eat time_sleep [meals]");
	}
	return (0);
}
