/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:07:13 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/18 01:12:41 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_table				*table;
	t_mtx				philo_mutex;
	long				start_philo;
}						t_philo;

struct					s_table
{
	long				num_philo;
	long				time2die;
	long				time2eat;
	long				time2sleep;
	long				nbr_meals;
	long				start_dinner;
	bool				end_dinner;
	pthread_t			monitor;
	t_mtx				table_mtx;
	t_mtx				write_mtx;
	t_fork				*forks;
	t_philo				*philos;

	bool				all_thr_ready;
	long				thr_running_nbr;

};

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}						t_status;

typedef enum e_time_code
{
	SECOND,
	MILLISEC,
	MICROSEC
}						t_time_code;

int						parse_input(char **input);
int						start_dinner(t_table *table);
int						ft_atoi(const char *str);
long					gettime(t_time_code tcode);
void					my_usleep(long usec, t_table *table);

void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
bool					simulation_finished(t_table *table);

void					write_status(t_status status, t_philo *philo);
void					*monitor_dinner(void *data);
void					clean(t_table *table);

#endif