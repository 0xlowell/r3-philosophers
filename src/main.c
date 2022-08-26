//
// Created by Lowell Zima on 8/8/22.
//

#include "../includes/philosophers.h"


void	dinning(t_node *thread, pthread_mutex_t *fork)
{
	printf("thread->i_node %d\n", thread->i_node);
	(void)fork;

//	pthread_mutex_lock(&fork[0]);
//	pthread_mutex_unlock(&fork[0]);
}

//void	action(t_main *m, t_node *cur, long fork1, long fork2);

void	*routine(void *arg)
{
	t_main *m;
	t_node *thread;

	m = (t_main *)arg;
	thread = m->head;
	/* link the thread node number with the number of time it was called pthread_create
	 * so, thread->i_node < m->i_main means that we loop until we match the thread corresponding
	 * by reaching to the thread->next. All because, we only can get m->head, and we need to get to
	 * our right thread.
	 * */
	while (thread->i_node < m->i_main)
		thread = thread->next;
//	printf("m->thread %d: %p\n", thread->i_node, thread);

	if (m->arg.nbr_eat > 1)
	{
		dinning(thread, m->fork);
		usleep(1);
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
		usleep(1);
		cur = cur->next;
		i++;

	}
	cur = m->head;
	i = 0;
	while (cur != NULL && status == 0)
	{
		if (pthread_join(cur->id, NULL) != 0)
			return(ERROR);
		cur = cur->next;
		printf("finish %d\n", i);
		i++;
	}
	if (status != 0)
		return (ERROR);
	return (0);
}

//int did_eat(t_main *m)
//{
//	//todo
//}

//
int	main(int argc, char **argv)
{
	t_main	main;

	/* initialisation of basic tools: linked list, mutex, structures filled up with argv**
	 * get **argv data and transform into int, check error max and min int
	 * stock data int into used variables :
	 *
	 * argv[1] nb of philo
	 * argv[2] time to die
	 * argv[3] time to eat
	 * argv[4] time to sleep
	 * argv[5] optional argv: nb of time each philo must eat
	 *
	 * init linked list of threads:
		 * |_ create a linked chain for each philosopher
		 *		|_ start by init_lst, it while iterate with philo's number
		 * 		and add_node as much necessary
		 * 		|__ protect it with a status, returned from add_node, if the mem_alloc
		 *		for nodes goes sideways, deleted all nodes to avoid leaks.(del_lst)
		 *		|___ link prev-new-next nodes(add_node)
		 * |_ Set up mutex
		 * |_ int pthread_mutex_init(pthread_mutex_t * __restrict, const pthread_mutexattr_t * _Nullable __restrict);
		 * |__ 1st arg: create a mutex in main structure
		 * |__ 2nd arg: set as NULL -> the default mutex attributes are used
		 * |___ if it doesn't return (0) -> close the program
		 */
	if (parse_and_init(&main, argc, argv) == ERROR)
		return (exit_program(&main));
	/* gettimeofday(): start timeline in struct timeval *
	 * |_ int gettimeofday(struct timeval * __restrict, void * __restrict);
	 * 		struct timeval * is by default in lib.
	 * 		set void *, for default settings
	 */
	timestamp();
	//gettimeofday(&main.start, NULL);
	/* injected threads into linked chain created (as much as nb of philo)
	 * |_ loop on struct * to injecte pthread_create in struct philo -> id
	 * 		|__ int pthread_create(
	 * 			|___ pthread_t _Nullable * _Nonnull __restrict,
	 * 				|____ this arg is for identification of the thread
	 * 				const pthread_attr_t * _Nullable __restrict,
	 * 				|____ set NULL for default settings
	 * 				|ret -> void *|| fct-> _Nullable (* _Nonnull) || arg->(void * _Nullable),
	 * 				|____ fct p_thread to create ->
	 * 					|____
	 * 			void * _Nullable __restrict);
	 * 		|__ insert a usleep(1)
	 */
	if (init_lst(&main) != 0)
		return(exit_program(&main));
	if (thread_init(&main) == ERROR)
		return (exit_program(&main));
//	if (pthread_create(&main.checker, NULL, check_death, &main) != 0)
//		return(exit_program(&main));
}



//void	action(t_main *m, t_node *cur, long fork1, long fork2)
//{
//	printf("action\n");
//	pthread_mutex_lock(&(m->fork[fork1]));
//	print_take_fork(m, cur);
//	pthread_mutex_lock(&(m->fork[fork2]));
//	print_take_fork(m, cur);
//	print_eat(m, cur);
//	printf("action - m->arg.eat %ld\n", m->arg.eat);
//	usleep(m->arg.eat);
//	timestamp();
//	pthread_mutex_unlock(&m->fork[fork1]);
//	pthread_mutex_unlock(&m->fork[fork2]);
//	print_sleep(m, cur);
//	usleep(m->arg.sleep);
//	print_thinking(m, cur);
//}
//

//{
//	printf("launch dinning\n");
//	printf("i_node %d \n", cur->i_node);
//	m->i_main = (int)m->arg.nbr;
//	if (m->i_main == 1)
//		action(m, cur, 0, m->arg.nbr - 1);
//	if (m->i_main % 2 == 0)
//	{
//		action(m, cur, cur->i_node -1 , cur->i_node - 2);
//		usleep(800);
//	}
//	else
//		action(m, cur, cur->i_node - 1, cur->i_node - 2);
//}
//
//void	*routine(void *main)
//{
//	printf("routine\n");
//	t_main	*m;
//	t_node	*node;
//
//	m = (t_main *)main;
//	node = m->head;
//	timestamp();
//	while (node && node->next)
//		node = node->next;
//	node->eated = 0;
//	if (m->arg.nbr_eat != -1)
//	{
//		node->eated = 0;
//		while (/*m->d_or_a != 1*/ node->eated++ < m->arg.nbr_eat)
//			dinning(m, m->head);
//	}
//	else
//		while (m->d_or_a != 1)
//		{
//			printf("i_node in routine %d \n", node->i_node);
//			dinning(m, m->head);
//		}
//	return (0);
//}