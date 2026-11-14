/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:51:37 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/14 12:37:05 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	fifo(t_heap_node *n1, t_heap_node *n2)
{
	t_request	*request_1;
	t_request	*request_2;

	request_1 = (t_request *)n1->content;
	request_2 = (t_request *)n2->content;
	if (request_1->request_id > request_2->request_id)
		return (TRUE);
	return (FALSE);
}

int	edf(t_heap_node *n1, t_heap_node *n2)
{
	t_request	*request_1;
	t_request	*request_2;

	request_1 = (t_request *)n1->content;
	request_2 = (t_request *)n2->content;
	if (request_1->request_id > request_2->request_id)
		return (TRUE);
	return (FALSE);
}

static void	process_request(int dongle_id[2], t_scheduler *scheduler,
		t_heap_node *node_left, t_heap_node *node_right)
{
	t_request	*request_left;
	t_request	*request_right;

	request_left = (t_request *)node_left->content;
	request_right = (t_request *)node_right->content;
	if (request_left->coder_id == request_right->coder_id)
	{
		heap_pop(scheduler->heaps[dongle_id[LEFT]], fifo);
		heap_pop(scheduler->heaps[dongle_id[RIGHT]], fifo);
		assert(!pthread_mutex_lock(request_left->can_compile_mu));
		*request_left->can_compile = TRUE;
		assert(!pthread_mutex_unlock(request_left->can_compile_mu));
		assert(!pthread_cond_signal(request_left->can_compile_cond));
	}
}

void	who_can_compile(t_scheduler *scheduler)
{
	int			i;
	t_heap_node	*node_left;
	t_heap_node	*node_right;
	int			dongle_id[2];

	i = 0;
	while (i < scheduler->params[number_of_coders])
	{
		get_dongle_arr(i, scheduler->params, dongle_id);
		if (!scheduler->heaps[dongle_id[LEFT]]->heap_size
			|| !scheduler->heaps[dongle_id[RIGHT]]->heap_size)
		{
			i++;
			continue ;
		}
		node_left = scheduler->heaps[dongle_id[LEFT]]->queue[0];
		node_right = scheduler->heaps[dongle_id[RIGHT]]->queue[0];
		process_request(dongle_id, scheduler, node_left, node_right);
		i++;
	}
}

void	*scheduler_routine(void *data)
{
	t_scheduler	*scheduler;
	t_request	*request;
	t_heap_node	*node;
	int			dongle[2];

	scheduler = (t_scheduler *)data;
	while (get_sim_state(scheduler->simulation_state,
			scheduler->simulation_state_mu) == ON)
	{
		request = request_pop(scheduler->queue);
		if (request)
		{
			node = heap_new_node(request);
			get_dongle_arr(request->coder_id, scheduler->params, dongle);
			assert(heap_push(scheduler->heaps[dongle[LEFT]], node, fifo));
			assert(heap_push(scheduler->heaps[dongle[RIGHT]], node, fifo));
			who_can_compile(scheduler);
			usleep(100000);
		}
	}
	return (NULL);
}
