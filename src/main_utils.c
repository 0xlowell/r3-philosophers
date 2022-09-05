/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzima <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:19:34 by lzima             #+#    #+#             */
/*   Updated: 2022/08/29 19:19:37 by lzima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static long long	init_timestamp(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long long	timestamp(void)
{
	static long long	time;

	if (time == 0)
		time = init_timestamp();
	return (init_timestamp() - time);
}

int	exit_program(t_main *m)
{
	if (m->write)
	{
		pthread_mutex_destroy(m->write);
		free(m->write);
	}
	if (m->head)
	{
		free_fork(m);
		del_lst(&m->head, &m->tail);
	}
	m = NULL;
	return (-1);
}

void	free_fork(t_main *m)
{
	t_node	*cur;

	cur = m->head;
	while (cur)
	{
		pthread_mutex_destroy(&cur->fork);
		cur = cur->next;
	}
}

void	starvation(t_main *m)
{
	t_node	*cur;

	cur = m->head;
	while (cur)
	{
		pthread_join(cur->id, NULL);
		cur = cur->next;
	}
	exit_program(m);
}
