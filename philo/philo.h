/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:31 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/20 22:23:19 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define BLACK "\033[1;30m"
#define ORANGE "\033[1;91m"
#define PURPLE "\033[1;95m"

#define RESET "\033[0m"

/***
 * structures
 ***/

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
/*
 * FORK
 */

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

/*
 * PHILO
 */

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

}						t_philo;

/*
 * TABLE
 */

typedef struct s_table
{
	long				num_philo;
	long				time2die;
	long				time2eat;
	long				time2sleep;
	long				nbr_meals;
	long				start_dinner;
	long				thr_running_nbr;
	bool				end_dinner;
	pthread_t			monitor;
	t_mtx				table_mtx;
	t_mtx				write_mtx;
	t_fork				*forks;
	t_philo				*philos;
	bool				all_thr_ready;

}						t_table;

/***
 * ENUM
 ***/

typedef enum e_opcode
{
	CREATE,
	DESTROY,
	INIT,
	LOCK,
	UNLOCK,
	JOIN,
	DETACH
}						t_opcode;

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

/***
 * PROTOTYPES
 ***/

void					start_dinner(t_table *table);
void					data_init(t_table *table);
void					init_table(t_table *table, char **av);

/*
	write status
 */
void					write_status(t_status status, t_philo *philo);

/*
	safe functions
 */

void					*safe_malloc(size_t bytes);
void					safe_mutex_handel(t_mtx *mutex, t_opcode opcode);
void					safe_thread_handel(pthread_t *thr, void *(*foo)(void *),
							void *data, t_opcode opcode);

/*
	utils
 */

void					my_usleep(long usec, t_table *table);
long					gettime(t_time_code tcode);
void					error_exit(const char *error);
void					clean(t_table *table);
/*
	getters_setters
 */

void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
bool					simulation_finished(t_table *table);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_number);
void					increase_long(t_mtx *mutex, long *var);

/*
	monitoring
 */

void					*monitor_dinner(void *data);

/*
	syncro
 */

void					wait_all_threads(t_table *table);