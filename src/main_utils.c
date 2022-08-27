
#include "../includes/philosophers.h"

static long long    init_timestamp(void)
{
	struct timeval    tv;
	long long        time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long long    timestamp(void)
{
	static long long    time;

	if (time == 0)
		time = init_timestamp();
	return (init_timestamp() - time);
}

int	exit_program(t_main *m)
{
	if (m->write)
		free_write(m);
	if (!m->head)
		del_lst(&m->head, &m->tail);
	m = NULL;
	return (-1);
}

void	free_write(t_main *m)
{
	if (!m->write || m->write != NULL)
	{
		pthread_mutex_destroy(m->write);
		free(m->write);
		m->write = NULL;
	}
}

//void	free_fork(t_main *m)
//{
//	int	i;
//
//	if (!m->fork)
//	{
//		i = 0;
//		while (i < m->arg.nbr)
//			pthread_mutex_destroy(&m->fork[i++]);
//		free(m->fork);
//		m->fork = NULL;
//	}
//}

int	error_message(char *error)
{
	printf("%s", error);
	return (1);
}
