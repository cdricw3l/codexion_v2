/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:51:37 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:47:03 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

/* 
	n1->content and n2->content are same content. Only one content free
*/
static void	process_request(int dongle_id[2], t_scheduler *scheduler,
		t_heap_node *node_left, t_heap_node *node_right)
{
	t_request	*request_left;
	t_request	*request_right;
	t_heap_node	*n1;
	t_heap_node	*n2;

	request_left = (t_request *)node_left->content;
	request_right = (t_request *)node_right->content;
	
	
	
	if (request_left->coder_id == request_right->coder_id)
	{
		//printf("Scheduler process request :\n");
		//request_display_node(request_left);
		if (get_dongle_state(request_left->dongle_l) || get_dongle_state(request_left->dongle_r))
		{
			//printf(REDB"Decision NOK!"CRESET"\n\n");
			return ;
		}
		//printf(GRNB"Desision OK!"CRESET"\n\n");
		n1 = heap_pop(scheduler->heaps[dongle_id[LEFT]], fifo);
		n2 = heap_pop(scheduler->heaps[dongle_id[RIGHT]], fifo);
		assert(!pthread_mutex_lock(request_left->can_compile_mu));
		*request_left->can_compile = true;
		assert(*request_left->can_compile == true);
		set_dongle_state(request_left->dongle_l, true);
		set_dongle_state(request_left->dongle_r, true);
		assert(!pthread_cond_signal(request_left->can_compile_cond));
		assert(!pthread_mutex_unlock(request_left->can_compile_mu));

		free(n1->content);
		free(n1);
		free(n2);
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
		if (!scheduler->heaps[dongle_id[LEFT]]->heap_size || !scheduler->heaps[dongle_id[RIGHT]]->heap_size)
		{
			i++;
			continue ;
		}
		node_left = scheduler->heaps[dongle_id[LEFT]]->queue[0];
		node_right = scheduler->heaps[dongle_id[RIGHT]]->queue[0];
		if (node_left && node_right)
		{
			assert(node_left && node_right);
			process_request(dongle_id, scheduler, node_left, node_right);
		}
		i++;
	}
}

void *clean_request_queue(t_scheduler *scheduler)
{
	size_t i;
	size_t j;
	t_request *r;
	t_request **q;

	i = 0;
	q = scheduler->queue->queue;
	while (i < scheduler->queue->queue_size)
		pthread_cond_signal(q[i++]->can_compile_cond);
	i = 0;
	while (i < scheduler->params[number_of_coders])
	{
		j = 0;
		while(j < scheduler->heaps[i]->heap_size)
		{

			r = scheduler->heaps[i]->queue[j]->content;
			pthread_cond_signal(r->can_compile_cond);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	*scheduler_routine(void *data)
{
	t_scheduler	*scheduler;
	t_request	*request;
	t_heap_node	*node_1;
	t_heap_node	*node_2;
	int			dongle[2];

	scheduler = (t_scheduler *)data;
	while (get_sim_state(scheduler->simulation_state,
			scheduler->state_mu) == ON)
	{
		request = request_pop(scheduler->queue);
		if (request)
		{
			node_1 = heap_new_node(request);
			node_2 = heap_new_node(request);
			get_dongle_arr(request->coder_id, scheduler->params, dongle);
			assert(heap_push(scheduler->heaps[dongle[LEFT]], node_1, fifo));
			assert(heap_push(scheduler->heaps[dongle[RIGHT]], node_2, fifo));
		}
		who_can_compile(scheduler);
	}
	return (clean_request_queue(scheduler));
}
