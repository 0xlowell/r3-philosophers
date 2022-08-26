//
// Created by Lowell Zima on 8/8/22.
//

#include "../includes/philosophers.h"

void	print_take_fork(t_main *m, t_node *cur)
{
	//todo Bug when this fonction is called, exit the program weirdly and
	// EXIT
	gettimeofday(&cur->now, NULL);
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.lld \t 🥄 %d node has taken a fork\n", timestamp(), cur->i_node);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);
}

void	print_eat(t_main *m, t_node *cur)
{
	gettimeofday(&cur->now, NULL);
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.lld \t 🥄 %d node eat\n", timestamp(), cur->i_node);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);

}

void	print_sleep(t_main *m, t_node *cur)
{
	gettimeofday(&cur->now, NULL);
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.lld \t 🥄 %d node sleep\n", timestamp(), cur->i_node);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);
}

void	print_thinking(t_main *m, t_node *cur)
{
	gettimeofday(&cur->now, NULL);
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.lld \t 🥄 %d node think\n", timestamp(), cur->i_node);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);
}

void	print_death(t_main *m, t_node *cur)
{
	gettimeofday(&cur->now, NULL);
	pthread_mutex_lock(m->write);
	printf("_______________________________________________________\n");
	printf("\n ⏰ %.lld \t 🥄 %d node died\n", timestamp(), cur->i_node);
	printf("_______________________________________________________\n");
	pthread_mutex_unlock(m->write);
}