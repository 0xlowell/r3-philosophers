//
// Created by Lowell Zima on 8/8/22.
//

#include "../includes/philosophers.h"

void	action(t_main *m, t_philo *p, long fork1, long fork2)
{
	pthread_mutex_lock(&(m->fork[fork1]));
	print_take_fork(m, p);
	pthread_mutex_lock(&(m->fork[fork2]));
	print_take_fork(m, p);
	print_eat(m, p);
	usleep(m->arg.eat);
	timestamp();
	pthread_mutex_unlock(&m->fork[fork1]);
	pthread_mutex_unlock(&m->fork[fork2]);
	print_sleep(m, p);
	usleep(m->arg.sleep);
	print_thinking(m, p);
}

void	dinning(t_main *m, t_philo* p)
{
	m->nbr_p = m->arg.nbr;
	if (m->nbr_p == 1)
		action(m, p, 0, m->arg.nbr - 1);
	if (m->nbr_p % 2 == 0)
	{
		usleep(800);
		action(m, p, 1, 2);
	}
	else
		action(m, p, p->nbr_id - 1, p->nbr_id - 2);
}

void	*p_thread(void *mm)
{
	t_main *m;
	m = (t_main *)mm;

//	gettimeofday(&m->p->time_eat, NULL);
	if (m->arg.nbr_eat != -1)
	{
		m->p->eated = 0;
		while (m->d_or_a != 1 && m->p->eated++ < m->arg.nbr_eat)
			dinning(m, m->p);
	}
	else
		while (m->d_or_a != 1)
			dinning(m, m->p);
	return (0);
}

void	init_philo(t_main *m)
{
	if (m)
	{
		m->p = malloc(m->arg.nbr * sizeof(int));
		mem_check(m->p);
	}

}

int thread_init(t_main *m)
{
	int status;
	int i;

	init_philo(m);
	status = 0;
	i = 0;
	while (i < m->arg.nbr && status == 0)
	{
		status = pthread_create(&m->p[i].id, NULL, p_thread, m);
		usleep(1);
		m->p->nbr_id = i;
		i++;
	}
	if (status != 0)
		return (ERROR);
	return (0);
}

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
	gettimeofday(&main.start, NULL);
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
	if (thread_init(&main) == ERROR)
		return (exit_program(&main));
}
