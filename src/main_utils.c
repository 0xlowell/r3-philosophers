
#include "philosophers.h"
#include "utils.h"


int	error_message(char *error)
{
	printf("%s", error);
	return (1);
}

int	exit_program(t_main *m)
{
	if (m->fork != NULL)
		free_f_nd_p(m);
	if (m->p != NULL)
		free_f_nd_p(m);
	m = NULL;
}

void	free_f_nd_p(t_main *m)
{
	int	i;

	if (m->fork != NULL)
	{
		i = 0;
		while (i < m->arg.nbr)
			pthread_mutex_destroy(&m->fork[i++]);
		free(m->fork);
		m->fork = NULL;
	}
	if (m->p != NULL)
	{
		i = 0;
		while (i < m->arg.nbr)
			free(&m->p[i++]);
		free(m->p);
		m->p = NULL;
	}
}

double	timer_ms(struct timeval start, struct timeval now)
{
	double	pass;
	double	upass;

	pass = (double)now.tv_sec - (double)start.tv_sec;
	upass = now.tv_usec - start.tv_usec;
	return ((pass * 1000) + (upass / 1000));
}
