
/* general rules
 *
 * Errors:
 * if a error occurs, it will be handle with ERROR macro
 * or with error_message()
 *
 * if it's error_message(), it means that no memory was allocated in the process
 * if it's ERROR, it means :
 * 		- it's a return from exit_program()
 * 		-
*/
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*
 * Authorized Functions Library
*/

# include <string.h>	/* memset function */
# include <stdio.h> 	/* printf function */
# include <stdlib.h>	/* malloc, free functions */
# include <stddef.h>	/* Size_t variable */
# include <unistd.h>	/* write, usleep functions */
# include <sys/time.h>	/* gettimeofday function */
# include <pthread.h>	/* threads and mutex functions */

/*
 * Default Library
*/

# include "philosophers.h"

/*
 * Macro for error
*/

# define INT_MAX 	2147483647
# define INT_MIN 	-2147483648
# define NARG 		"\n❌ Number of arguments incorrect, use 4 or 5 arguments\n"
# define NPHILO 	"\n❌ Number of philosophers too low, use at least one, max 200\n"
# define INT_LIM 	"\n❌ Args value exceed limit required\n"
# define NDIGIT 	"\n❌ Args value aren't digits\n"
# define ERROR		1
# define TRUE		0
# define FALSE		-1

/*
 * Variables Structures
*/

typedef struct	s_arg
{
	long 			nbr;		/*number_of_philosophers:
 * The number of philosophers and also the number of forks.*/
	long 			death;		/*time_to_die (in milliseconds):
 * If a philosopher didn’t start eating time_to_die milliseconds since the beginning
 * of their last meal or the beginning of the sim- ulation, they die.*/
	long 			eat;		/*time_to_eat (in milliseconds):
 * The time it takes for a philosopher to eat. During that time, they will need to hold two forks.*/
	long 			sleep;		/*time_to_sleep (in milliseconds):
 * The time a philosopher will spend sleeping.*/
	long 			nbr_eat;	/*number_of_times_each_philosopher_must_eat (optional argument):
 * If all philosophers have eaten at least
 * number_of_times_each_philosopher_must_eat times, the simulation stops.
 * If not specified, the simulation stops when a philosopher dies.*/
}			t_arg;

typedef struct s_node
{
	struct s_node	*next;		/*next node*/
	struct s_node	*prev;		/*previous node*/
	pthread_t 		id;
	int 			i_node;
	struct timeval	time_eat;
	int 			eated;
	struct timeval	now;
}			t_node;

typedef struct s_main
{
	t_arg			arg;		/*data*/
	pthread_mutex_t *fork;		/*mutex, known as "fork" in philosophers dinning problems*/
	int 			nbr_p;
	int 			i_main;
	int				d_or_a;		/*states*/
	pthread_t 		checker;
	pthread_mutex_t	*write;		/* lock writing in term */
	struct timeval	start;		/*start of gettimeofday()*/
	t_node			*head;		/*head node of linked list node*/
	t_node			*tail;		/*tail node of linked list node*/
}			t_main;

/* ---- Files .c ---- */
/*
 * main.c
 */
int		main(int argc, char **argv);
void	print_take_fork(t_main *m, t_node *p);
void	action(t_main *m, t_node *p, long fork1, long fork2);
void	dinning(t_main *main, t_node *thread,  pthread_mutex_t* p);
void	*routine(void *main);
int 	thread_init(t_main *m);
/*
 * main_utils.c
*/
int		error_message(char *error);							/*print *error message*/
int		exit_program(t_main *m);							/*exit program in a proper way*/
void	free_fork(t_main *m);
void	free_write(t_main *m);
double	timer_ms(struct timeval start, struct timeval now);
long long    timestamp(void);
/*
 * parsing.c DONE
*/
int		parse_args(t_main *m, int argc, char **argv);		/*store argv into struct arg*/
int		error_arg_digit(int argc, char **argv);
int		error_args_limit(t_main *m);						/*handle argv's error*/
int		set_up_f_nd_p(t_main *m);								/*fill up fork allocated memory with pthread_mutex_t*/
int		parse_and_init(t_main *m, int argc, char **argv);	/*sub-main for parsing and initialisation*/
/*
 * libft_utils.c
*/
int		mem_check(void *ptr);								/*memory allocation security*/
int	ft_isdigit(int c);										/*RTFM*/
long	ft_atol(const char *str);
void	*ft_calloc(size_t count, size_t size);
//void	*ft_bzero(void *s, size_t n);
void    *ft_memset(void *b, int c, size_t len);

/*
 * print.c
*/
void	print_take_fork(t_main *m, t_node *p);
void	print_eat(t_main *m, t_node *p);
void	print_sleep(t_main *m, t_node *p);
void	print_thinking(t_main *m, t_node *p);
/*
 * linked_list.c
 */
void	last_del_lst(t_node **tail);
int	del_lst(t_node	**head, t_node **tail);
int	add_node(t_node **head, t_node **tail, int nbr);
int	init_lst(t_main *m);


#endif
