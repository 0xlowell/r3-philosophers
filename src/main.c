//
// Created by Lowell Zima on 8/8/22.
//


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

/* gettimeofday(): start timeline in struct timeval *
	 * |_ int gettimeofday(struct timeval * __restrict, void * __restrict);
	 * 		struct timeval * is by default in lib.
	 * 		set void *, for default settings
	 */

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

#include "../includes/philosophers.h"

//todo link dinning fonction with limit and set up checker for death

int	main(int argc, char **argv)
{
	t_main	main;

	if (parse_and_init(&main, argc, argv) == ERROR)
		return (exit_program(&main));

	if (init_lst(&main) != 0)
		return(exit_program(&main));
	if (thread_init(&main) == ERROR)
	{
		printf("error init\n");
		return (exit_program(&main));
	}
	while (main.d_or_a != 1)
		usleep(100);
}
