/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzima <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:24:27 by lzima             #+#    #+#             */
/*   Updated: 2022/08/29 19:24:31 by lzima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	unlock_sleep_think(t_main *m, t_node *thread)
{
	pthread_mutex_unlock(&thread->fork);
	if (thread->next != NULL)
		pthread_mutex_unlock(&thread->next->fork);
	else
		pthread_mutex_unlock(&m->head->fork);
	print_sleeping(m, thread);
	if (m->d_or_a == 0)
		ft_usleep(m->arg.sleep);
	print_thinking(m, thread);
}

void	dinning(t_main *m, t_node *thread)
{
	pthread_mutex_lock(&thread->fork);
	print_fork(m, thread);
	if (m->arg.nbr == 1)
	{
		pthread_mutex_unlock(&thread->fork);
		while (m->d_or_a == 0)
			;
		return ;
	}
	if (thread->next != NULL)
	{
		pthread_mutex_lock(&thread->next->fork);
		print_fork(m, thread);
	}
	else
	{
		pthread_mutex_lock(&m->head->fork);
		print_fork(m, thread);
	}
	print_eating(m, thread);
	thread->last_supper = timestamp();
	if (m->d_or_a == 0)
		ft_usleep(m->arg.eat);
	unlock_sleep_think(m, thread);
}

void	*routine(void *arg)
{
	t_main	*m;
	t_node	*thread;

	m = (t_main *)arg;
	thread = m->head;
	pthread_mutex_lock(m->write);
	while (thread->i_node < m->i_main)
		thread = thread->next;
	m->i_main++;
	pthread_mutex_unlock(m->write);
	if (thread->i_node % 2 != 0)
		ft_usleep(m->arg.eat);
	while (m->d_or_a == 0 && (thread->eated < m->arg.nbr_eat || \
	m->arg.nbr_eat == -1))
		dinning (m, thread);
	return (0);
}

int	thread_init(t_main *m)
{
	int		status;
	t_node	*cur;

	status = 0;
	cur = m->head;
	m->i_main = 0;
	while (cur != NULL && status == 0)
	{
		status = pthread_create(&cur->id, NULL, routine, m);
		cur = cur->next;
	}
	if (status != 0)
		return (ERROR);
	return (0);
}

int	error_message(char *error)
{
	printf("%s", error);
	return (1);
}
