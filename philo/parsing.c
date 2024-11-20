/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:07:10 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/17 15:30:45 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	result;

	result = 0;
	i = 0;
	while (str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + str[i] - 48;
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return ((int)result);
}

static int	is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (-1);
	}
	return (0);
}

int	parse_input(char **input)
{
	int	i;

	i = 0;
	while (input[++i])
	{
		if (is_digit(input[i]) == -1 || ft_atoi(input[i]) == -1)
		{
			printf("Integer arg required\n");
			return (1);
		}
	}
	if (ft_atoi(input[2]) < 60 || ft_atoi(input[3]) < 60
		|| ft_atoi(input[4]) < 60 || ft_atoi(input[1]) > 200
		|| ft_atoi(input[1]) < 1)
	{
		printf("Arg not valid\n");
		return (1);
	}
	return (0);
}

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
	free(table->forks);
	free(table->philos);
}
