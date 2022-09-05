/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzima <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:59:55 by lzima             #+#    #+#             */
/*   Updated: 2022/08/29 19:00:09 by lzima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	count_meal(t_main *m)
{
	m->count++;
	if (m->count == m->arg.nbr)
		m->d_or_a = 1;
}

static int	dont_starve(t_main *m, t_node *cur)
{
	m->d_or_a = 1;
	print_died(m, cur);
	printf("\t ⚰️ time_to_die is reach without dinner \n");
	return (1);
}

static int	finnish_eating(t_main *m)
{
	m->d_or_a = 1;
	pthread_mutex_lock(m->write);
	printf("%lld \t 💩 finish eating \n", timestamp());
	pthread_mutex_unlock(m->write);
	return (1);
}

int	its_a_good_day_to_die(t_main *m)
{
	t_node	*cur;
	int		check;

	check = 0;
	m->count = 0;
	cur = m->head;
	while (cur)
	{
		if (m->arg.nbr_eat != -1 && cur->eated >= m->arg.nbr_eat)
		{
			count_meal(m);
			if (m->d_or_a == 1)
				break ;
		}
		m->now = timestamp();
		if (m->now - cur->last_supper >= m->arg.death)
		{
			check = dont_starve(m, cur);
			break ;
		}
		cur = cur->next;
	}
	if (m->count == m->arg.nbr)
		return (finnish_eating(m));
	return (check);
}

int	main(int argc, char **argv)
{
	t_main	main;

	ft_memset(&main, 0, sizeof(t_main));
	if (parse_and_init(&main, argc, argv) == ERROR)
		return (exit_program(&main));
	if (init_lst(&main) != 0)
		return (exit_program(&main));
	if (thread_init(&main) == ERROR)
		return (exit_program(&main));
	while (main.d_or_a != ERROR && its_a_good_day_to_die(&main) != ERROR)
		usleep(100);
	starvation(&main);
}
