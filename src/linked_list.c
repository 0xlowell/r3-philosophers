/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzima <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:59:06 by lzima             #+#    #+#             */
/*   Updated: 2022/08/29 18:59:34 by lzima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	del_lst(t_node	**head, t_node **tail)
{
	while (*head != *tail)
		last_del_lst(tail);
	free(*head);
	*head = NULL;
	*tail = NULL;
	return (1);
}

void	last_del_lst(t_node **tail)
{
	t_node	*del;

	del = *tail;
	*tail = del->prev;
	free(del);
}

int	add_node(t_node **head, t_node **tail, int nbr)
{
	t_node	*cur;

	cur = ft_calloc(1, sizeof(t_node));
	if (mem_check(cur) == 1)
		return (1);
	cur->next = NULL;
	cur->prev = NULL;
	cur->i_node = nbr;
	if (pthread_mutex_init(&cur->fork, NULL) != 0)
		return (1);
	if (*head == NULL)
	{
		*head = cur;
		*tail = cur;
	}
	else
	{
		(*tail)->next = cur;
		cur->prev = (*tail);
		*tail = cur;
	}
	return (0);
}

int	init_lst(t_main *m)
{
	int	check;

	m->head = NULL;
	m->tail = NULL;
	m->i_main = 0;
	check = 0;
	while (m->i_main < m->arg.nbr && check != 1)
	{
		check = add_node(&m->head, &m->tail, m->i_main);
		m->i_main++;
	}
	if (check == 1)
		check = del_lst(&m->head, &m->tail);
	return (check);
}

int	mem_check(void *ptr)
{
	if (ptr == NULL)
		return (1);
	return (0);
}
