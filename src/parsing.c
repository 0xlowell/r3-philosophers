//
// Created by Lowell Zima on 8/8/22.
//

#include "../includes/philosophers.h"

int set_up_f_nd_p(t_main *m)
{
	int i;

	i = 0;
	while (i < m->arg.nbr)
		if (pthread_mutex_init(&(m->fork[i++]), NULL) != 0)
			return (exit_program(m));
	//if ((pthread_mutex_init(m->write, NULL)) != 0)
		//return (exit_program(m));
	return (0);
}

int error_args_limit(t_main *m)
{
	if (m->arg.nbr <= 0 || m->arg.nbr > INT_MAX)
		return (error_message(INT_LIM));
	if (m->arg.nbr < 1)
		return (error_message(NPHILO));
	if (m->arg.death <= 0 || m->arg.death < INT_MIN || m->arg.death > INT_MAX)
		return (error_message(INT_LIM));
	if (m->arg.eat <= 0 || m->arg.eat < INT_MIN || m->arg.eat > INT_MAX)
		return (error_message(INT_LIM));
	if (m->arg.sleep <= 0 || m->arg.sleep < INT_MIN || m->arg.sleep > INT_MAX)
		return (error_message(INT_LIM));
	if (!m->arg.nbr_eat)
		if (m->arg.nbr_eat <= 0 || m->arg.nbr_eat < INT_MIN || m->arg.nbr_eat > INT_MAX)
			return (error_message(INT_LIM));
	return (0);
}

int	error_arg_digit(int argc, char **argv)
{
	int i;
	int	y;

	i = 0;
	y = 0;
	while (++i < argc)
	{
		printf("av = %s\n", argv[i]);
		while (argv[i][y] == ft_isdigit(argv[i][y]))
			y++;
		if (ft_isdigit(argv[i][y] == 0))
			return (1);
		y++;
	}
	return (0);
}

int parse_args(t_main *m, int argc, char **argv)
{
	/*check if arguments are digits*/
	if (error_arg_digit(argc, argv) == ERROR)
		return (error_message(NDIGIT));
	/* set argv** into main_struct */
	m->arg.nbr = ft_atol(argv[1]);
	m->arg.death = ft_atol(argv[2]);
	m->arg.eat = ft_atol(argv[3]);
	m->arg.sleep = ft_atol(argv[4]);
	/* set dead_or_alive to 0 for later */
	m->d_or_a = 0;
	/* arg: number_of_times_each_philosopher_must_eat*/
	if (argv[5] != NULL)
		m->arg.nbr_eat = ft_atol(argv[5]);
	else
		m->arg.nbr_eat = -1;
	/* usleep fct is in microseconds, our input is in milli */
	m->arg.eat *= 1000;
	m->arg.sleep *= 1000;
	/* memory allocation for mutex (empty), known as "fork" ready to be filled in process*/
	m->fork = ft_calloc(m->arg.nbr, sizeof(pthread_mutex_t));
	if (mem_check(m->fork) == 1)
		return (ERROR);
	/* check error in arguments */
	if (error_args_limit(m) == ERROR)
		return (ERROR);
	return(0);
}

int	parse_and_init(t_main *m, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_message(NARG));
	if (parse_args(m, argc, argv) == ERROR)
		return (ERROR);
	if (set_up_f_nd_p(m) == ERROR)
		return(ERROR);
	timestamp();
	return (0);
}
