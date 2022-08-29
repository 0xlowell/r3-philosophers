//
// Created by Lowell Zima on 8/8/22.
//

#include "../includes/philosophers.h"


void	print_died(t_main *m, t_node *thread)
{
	pthread_mutex_lock(m->write);
	printf("%lld \t ⚰️ %d died \n", timestamp(), thread->i_node);
	pthread_mutex_unlock(m->write);
}

void	print_fork(t_main *m, t_node* thread)
{
	pthread_mutex_lock(m->write);
	if (m->d_or_a == 0)
		printf("%lld \t 🔧 %d has taken a fork\n", timestamp(), thread->i_node);
	pthread_mutex_unlock(m->write);
}

void	print_eating(t_main *m, t_node *thread)
{
	pthread_mutex_lock(m->write);
	if (m->d_or_a == 0)
		printf("%lld \t 🛠 %d is eating \t %d meal(s) \n", timestamp(), thread->i_node, thread->eated);
	pthread_mutex_unlock(m->write);
}

void	print_sleeping(t_main *m, t_node *thread)
{
	pthread_mutex_lock(m->write);
	if (m->d_or_a == 0)
		printf("%lld \t 😴 %d is sleeping \n", timestamp(), thread->i_node);
	pthread_mutex_unlock(m->write);
}

void	print_thinking(t_main *m, t_node *thread)
{
	pthread_mutex_lock(m->write);
	if (m->d_or_a == 0)
		printf("%lld \t 😩 %d is thinking \n", timestamp(), thread->i_node);
	pthread_mutex_unlock(m->write);
}