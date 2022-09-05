/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzima <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:21:12 by lzima             #+#    #+#             */
/*   Updated: 2022/08/29 19:21:20 by lzima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	set_up_f_nd_p(t_main *m)
{
	m->write = ft_calloc(1, sizeof(pthread_mutex_t));
	if ((pthread_mutex_init(m->write, NULL)) != 0)
		return (ERROR);
	return (0);
}

int	error_args_limit(t_main *m)
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
		if (m->arg.nbr_eat <= 0 || m->arg.nbr_eat < INT_MIN || \
		m->arg.nbr_eat > INT_MAX)
			return (error_message(INT_LIM));
	return (0);
}

int	error_arg_digit(int argc, char **argv)
{
	int	i;
	int	y;

	i = 0;
	while (++i < argc)
	{
		y = 0;
		while (ft_isdigit(argv[i][y]) != 0)
			y++;
		if (argv[i][y] != '\0')
			return (1);
	}
	return (0);
}

int	parse_args(t_main *m, int argc, char **argv)
{
	if (error_arg_digit(argc, argv) == ERROR)
		return (error_message(NDIGIT));
	m->arg.nbr = ft_atol(argv[1]);
	m->arg.death = ft_atol(argv[2]);
	m->arg.eat = ft_atol(argv[3]);
	m->arg.sleep = ft_atol(argv[4]);
	m->d_or_a = 0;
	if (argv[5] != NULL)
		m->arg.nbr_eat = ft_atol(argv[5]);
	else
		m->arg.nbr_eat = -1;
	m->arg.eat *= 1000;
	m->arg.sleep *= 1000;
	if (error_args_limit(m) == ERROR)
		return (ERROR);
	return (0);
}

int	parse_and_init(t_main *m, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_message(NARG));
	if (parse_args(m, argc, argv) == ERROR)
		return (ERROR);
	if (set_up_f_nd_p(m) == ERROR)
		return (ERROR);
	timestamp();
	return (0);
}
