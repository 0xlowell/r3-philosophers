
#include "../includes/philosophers.h"

//void	dead_or_alive(t_main *m, t_node *cur)
//{
//	printf("tst\n");
//	printf("cur->now:%lld \t - cur->last_supper:%lld = %lld\t > %ld\n", cur->now, cur->last_supper, ( cur->now - cur->last_supper), m->arg.death);
//	cur->last_supper = cur->now;
//	cur->now = timestamp();
//	if (cur->now - cur->last_supper >= m->arg.death)
//	{
//		m->d_or_a = 1;
//		print_died(m, cur);
//		printf("died in dead_or_alive\n");
//	}
//}

void	dinning(t_main *m, t_node *thread)
{
	pthread_mutex_lock(&thread->fork);
	print_fork(m, thread);
	if (m->arg.nbr == 1)
	{
		pthread_mutex_unlock(&thread->fork);
//		m->d_or_a = 1;
		while (m->d_or_a == 0)
			;
		return ;
//		print_died(m, thread);
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
	pthread_mutex_lock(m->write);
	while (thread->i_node < m->i_main)
		thread = thread->next;
	m->i_main++;
	pthread_mutex_unlock(m->write);
	if (thread->i_node % 2 != 0)
		usleep(m->arg.eat);
	while (m->d_or_a == 0 && (thread->eated < m->arg.nbr_eat || m->arg.nbr_eat == -1))
		dinning(m, thread);
	return(0);
}

int thread_init(t_main *m)
{
	int		status;
	int		i;
	t_node	*cur;

	status = 0;
	cur = m->head;
	m->i_main = 0;
	i = 0;
	while (cur != NULL && status == 0)
	{
		status = pthread_create(&cur->id, NULL, routine, m);
//		usleep(100);
		cur = cur->next;
		i++;
	}
	if (status != 0)
		return (ERROR);
	return(0);
}

void	starvation(t_main *m)
{
	t_node *cur;

	cur = m->head;
	while (cur)
	{
		pthread_join(cur->id, NULL);
		cur = cur->next;
	}
	exit_program(m);
}
