/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:51:37 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 03:50:33 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int64_t get_last_used(t_dongles *dongle)
{
	int64_t last_used;

	pthread_mutex_lock(&dongle->is_used_mu);
	last_used= dongle->last_use;
	pthread_mutex_unlock(&dongle->is_used_mu);
	return(last_used);
}

bool	check_cooldown(t_request *request, int params[8])
{
	int64_t now;
	int64_t last_used_l;
	int64_t last_used_r;

	now = get_now();
	last_used_l = get_last_used(request->dongle_l);
	last_used_r = get_last_used(request->dongle_r);
	if ((now - last_used_l) < ((int64_t)params[dongle_cooldown]) * 1000000)
		return (false);
	if ((now - last_used_r) < ((int64_t)params[dongle_cooldown]) * 1000000)
		return (false);
	return (true);
}

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
	if (request_left == request_right)
	{
		if (get_dongle_state(request_left->dongle_l)
			|| get_dongle_state(request_left->dongle_r)
			|| !check_cooldown(request_left, scheduler->params))
			return ;
		n1 = heap_pop(scheduler->heaps[dongle_id[LEFT]], fifo);
		n2 = heap_pop(scheduler->heaps[dongle_id[RIGHT]], fifo);
		pthread_mutex_lock(request_left->can_compile_mu);
		*request_left->can_compile = true;
		set_dongle_state(request_left->dongle_l, true, 0);
		set_dongle_state(request_left->dongle_r, true, 0);
		pthread_cond_signal(request_left->can_compile_cond);
		pthread_mutex_unlock(request_left->can_compile_mu);
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
			process_request(dongle_id, scheduler, node_left, node_right);
		i++;
	}
}

void	*clean_request_queue(t_scheduler *scheduler)
{
	size_t		i;
	size_t		j;
	t_request	*r;
	t_request	**q;

	i = 0;
	q = scheduler->queue->queue;
	while (i < scheduler->queue->queue_size)
		pthread_cond_signal(q[i++]->can_compile_cond);
	i = 0;
	while ((int)i < scheduler->params[number_of_coders])
	{
		j = 0;
		while (j < scheduler->heaps[i]->heap_size)
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
	while (get_sim_state(scheduler->sim_state,
			scheduler->state_mu) == ON)
	{
		who_can_compile(scheduler);
		request = request_pop(scheduler->queue);
		if (!request)
			continue;
		node_1 = heap_new_node(request);
		node_2 = heap_new_node(request);
		get_dongle_arr(request->coder_id, scheduler->params, dongle);
		heap_push(scheduler->heaps[dongle[LEFT]], node_1, fifo);
		heap_push(scheduler->heaps[dongle[RIGHT]], node_2, fifo);
	}
	return (clean_request_queue(scheduler));
}
