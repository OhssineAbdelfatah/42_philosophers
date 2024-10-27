/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:14:50 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/20 22:24:12 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		return (error_exit("error with malloc\n"), NULL);
	return (ret);
}

static void	handel_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid.\n");
	else if (EINVAL == status && opcode == INIT)
		error_exit("The value specified by attr is invalid.\n");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if \
		the thread blocked waiting for mutex.\n");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.\n");
	else if (EBUSY == status)
		error_exit("Mutex is locked.\n");
}

static void	handel_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("no resources to create another thread.\n");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission.\n");
	else if (EINVAL == status && CREATE == opcode)
		error_exit(" The value specified by attr is invalid.\n");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("the value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to\
			that specified by the given thread ID,thread.\n");
	else if (EDEADLK == status)
		error_exit(" A deadlock was detected or the value\
			of thread specifies the calling thread.\n");
}

void	safe_mutex_handel(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handel_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handel_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handel_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handel_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode use\n <LOCK> <UNLOCK> <INIT> <DESTROY>\n");
}

void	safe_thread_handel(pthread_t *thr, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	if (CREATE == opcode)
		handel_thread_error(pthread_create(thr, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handel_thread_error(pthread_join(*thr, NULL), opcode);
	else if (DETACH == opcode)
		handel_mutex_error(pthread_detach(*thr), opcode);
	else
		error_exit("Wrong opcode use\n <CREATE> <JOIN> <DETACH> \n");
}
