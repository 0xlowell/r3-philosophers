
#include "../includes/philosophers.h"

int its_a_good_day_to_die(t_main *m)
{
	t_node *cur;

	m->count = 0;
	cur = m->head;
	while (cur)
	{
		/* how many time they eat, all full ? stop*/
		if (m->arg.nbr_eat != -1 && cur->eated >= m->arg.nbr_eat)
		{
			m->count++;
			if (m->count == m->arg.nbr)
			{
				m->d_or_a = 1;
				break;
			}
		}
		m->now = timestamp();
		if (m->now - cur->last_supper >= m->arg.death)
		{
			m->d_or_a = 1;
			print_died(m, cur);
			printf("died : %lld time of die is reach without dinner \n", cur->now);
			return (1);
		}
		cur = cur->next;
	}
	if (m->count == m->arg.nbr)
	{
		m->d_or_a = 1;
		pthread_mutex_lock(m->write);
		printf("%lld \t finnish eating \n", timestamp());
		pthread_mutex_unlock(m->write);
		return (1);
	}
	return (0);
}

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
	while (main.d_or_a != ERROR && its_a_good_day_to_die(&main) != ERROR)
		usleep(100);
	starvation(&main);
}
