//
// Created by Lowell Zima on 8/8/22.
//

#include "../includes/philosophers.h"

void	print_take_fork(t_main *m, t_philo *p)
{
	//todo Bug when this fonction is called, exit the program weirdly and
	// EXIT
	timestamp();
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.1f \t 🥄 %ld Philo has taken a fork\n",
		   timer_ms(m->start, p->now), p->nbr_id);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);
}

void	print_eat(t_main *m, t_philo *p)
{
	gettimeofday(&p->now, NULL);
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.1f \t 🥄 %ld Philo eat\n",
		   timer_ms(m->start, p->now), p->nbr_id);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);

}

void	print_sleep(t_main *m, t_philo *p)
{
	gettimeofday(&p->now, NULL);
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.1f \t 🥄 %ld Philo sleep\n",
		   timer_ms(m->start, p->now), p->nbr_id);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);
}

void	print_thinking(t_main *m, t_philo *p)
{
	gettimeofday(&p->now, NULL);
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.1f \t 🥄 %ld Philo is thinking\n",
		   timer_ms(m->start, p->now), p->nbr_id);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);
}

void	print_death(t_main *m, t_philo *p)
{
	gettimeofday(&p->now, NULL);
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.1f \t 🥄 %ld Philo died\n",
		   timer_ms(m->start, p->now), p->nbr_id);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);
}