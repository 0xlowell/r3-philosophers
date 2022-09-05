/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzima <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:58:21 by lzima             #+#    #+#             */
/*   Updated: 2022/08/29 18:58:27 by lzima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define NARG 		"\n ❌ Number of arguments incorrect, use 4 or 5 arguments\n"
# define NPHILO 	"\n ❌ Number of philosophers too low\n"
# define INT_LIM 	"\n ❌ Args value exceed limit required\n"
# define NDIGIT 	"\n ❌ Args value aren't digits\n"
# define ERROR		1
# define FALSE		-1

/*
 * Variables Structures
*/

typedef struct s_arg
{
	long	nbr;
	long	death;
	long	eat;
	long	sleep;
	long	nbr_eat;
}			t_arg;

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	pthread_t		id;
	pthread_mutex_t	fork;
	int				i_node;
	int				eated;
	long long		last_supper;
	long long		now;
}			t_node;

typedef struct s_main
{
	t_arg			arg;
	int				count;
	int				i_main;
	int				d_or_a;
	long long		now;
	pthread_mutex_t	*write;
	t_node			*head;
	t_node			*tail;
}			t_main;

/* ---- Files .c ---- */
/*
 * main.c
 */
int			main(int argc, char **argv);
int			its_a_good_day_to_die(t_main *m);
/*
 * main_utils.c
*/
int			exit_program(t_main *m);
void		free_fork(t_main *m);
long long	timestamp(void);
void		starvation(t_main *m);
/*
 * parsing.c
*/
int			parse_args(t_main *m, int argc, char **argv);
int			error_arg_digit(int argc, char **argv);
int			error_args_limit(t_main *m);
int			set_up_f_nd_p(t_main *m);
int			parse_and_init(t_main *m, int argc, char **argv);
/*
 * thread.c
 */
void		dinning(t_main *m, t_node *thread);
void		*routine(void *arg);
int			thread_init(t_main *m);
int			error_message(char *error);
/*
 * utils.c
*/
int			ft_isdigit(int c);
long		ft_atol(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		ft_usleep(long sleep);

/*
 * print.c
*/
void		print_died(t_main *m, t_node *thread);
void		print_fork(t_main *m, t_node *thread);
void		print_eating(t_main *m, t_node *thread);
void		print_sleeping(t_main *m, t_node *thread);
void		print_thinking(t_main *m, t_node *thread);
/*
 * linked_list.c
 */
void		last_del_lst(t_node **tail);
int			del_lst(t_node	**head, t_node **tail);
int			add_node(t_node **head, t_node **tail, int nbr);
int			init_lst(t_main *m);
int			mem_check(void *ptr);

#endif
