/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:28 by aohssine          #+#    #+#             */
/*   Updated: 2024/10/27 10:34:49 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
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

void	parse_input(char **input)
{
	int	i;

	i = 0;
	while (input[++i])
	{
		if (is_digit(input[i]) == -1 || ft_atoi(input[i]) == -1)
			error_exit("Integer arg required");
	}
	if (ft_atoi(input[2]) < 60 || ft_atoi(input[3]) < 60
		|| ft_atoi(input[4]) < 60 || ft_atoi(input[1]) > 200
		|| ft_atoi(input[1]) < 1)
		error_exit("Arg not valid");
	return ;
}

void	init_table(t_table *table, char **av)
{
	parse_input(av);
	table->num_philo = ft_atoi(av[1]);
	table->time2die = (long)ft_atoi(av[2]) * 1000;
	table->time2eat = ft_atoi(av[3]) * 1000;
	table->time2sleep = ft_atoi(av[4]) * 1000;
	table->nbr_meals = -1;
	if (av[5])
		table->nbr_meals = ft_atoi(av[5]);
	table->end_dinner = false;
	return ;
}
