//
// Created by Lowell Zima on 8/8/22.
//

#include "../includes/philosophers.h"



int dead_or_alive(t_main *m, t_node *thread)
{
	thread->last_supper = thread->now;
	thread->now = timestamp();
	if (thread->now - thread->last_supper >= m->arg.death)
	{
		m->d_or_a = 1;
		print_died(m, thread);
		return (1);
	}
	if (m->arg.nbr_eat != -1 && thread->eated >= m->arg.nbr_eat)
	{
		thread->full++;
		if (thread->full == m->arg.nbr - 1)
			m->d_or_a = 1;
		pthread_mutex_lock(m->write);
		printf("%lld \t 🤢 %d is full \n", timestamp(), thread->i_node);
		pthread_mutex_unlock(m->write);
		return (1);
	}
	return (0);
}

void	dinning(t_main *m, t_node *thread)
{
	dead_or_alive(m, thread);
	thread->eated++;
	pthread_mutex_lock(&thread->fork);
	print_fork(m, thread);
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
	if (m->d_or_a == 0)
		ft_usleep(m->arg.eat);
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

void	*routine(void *arg)
{
	t_main *m;
	t_node *thread;

	m = (t_main *)arg;
	thread = m->head;
	while (thread->i_node < m->i_main)
		thread = thread->next;
	while (m->d_or_a == 0 && m->arg.nbr_eat >= thread->eated)
	{
		if (m->arg.nbr % 2 == 0)
		{
			usleep(400);
			dinning(m, thread);
		}
		else
		{
			usleep(200);
			dinning(m, thread);
		}
	}
	return(0);
}

int thread_init(t_main *m)
{
	int		status;
	int		i;
	t_node	*cur;

	status = 0;
	cur = m->head;
	i = 0;
	while (cur != NULL && status == 0)
	{
		m->i_main = i;
		status = pthread_create(&cur->id, NULL, routine, m);
//		cur->start = timestamp();
		usleep(100);
		cur = cur->next;
		i++;
	}
	if (status != 0)
		return (ERROR);
	return(0);
}
//
//void	check_death(void *arg)
//{
//	t_main *m;
//	t_node *cur;
//
//	m = (t_main *)arg;
//	cur = m->head;
//	while (m->d_or_a == 0)
//	{
//		if (dead_or_alive(m, cur) == 1)
//			break;
//		cur = cur->next;
//	}
//	starvation(m);
//}

void	starvation(t_main *m)
{
	t_node *cur;

	cur = m->head;
	while (cur)
	{
		pthread_join(cur->id, NULL);
		cur = cur->next;
	}
}
