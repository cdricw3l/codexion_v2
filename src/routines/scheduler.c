/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:51:37 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 21:46:54 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	*clean_request_queue(t_scheduler *scheduler)
{
	size_t		i;
	size_t		j;
	t_request	*r;
	t_heap_node	*h;

	request_clear_queue(scheduler->queue);
	i = 0;
	while ((int)i < scheduler->params[number_of_coders])
	{
		j = 0;
		while (j < scheduler->heaps[i]->heap_size)
		{
			h = heap_pop(scheduler->heaps[i], fifo);
			r = (t_request *)h->content;
			pthread_mutex_lock(r->can_compile_mu);
			*r->can_compile = true;
			pthread_cond_signal(r->can_compile_cond);
			pthread_mutex_unlock(r->can_compile_mu);
			free(r);
			j++;
			free(h);
		}
		i++;
	}
	return (NULL);
}

static bool	check_cooldown(t_request *request, int params[8])
{
	int64_t	now;
	int64_t	last_used_l;
	int64_t	last_used_r;

	now = get_now();
	last_used_l = get_last_use(request->dongle_l);
	last_used_r = get_last_use(request->dongle_r);
	if ((now - last_used_l) < ((int64_t)params[dongle_cooldown]) * 1000000)
		return (false);
	if ((now - last_used_r) < ((int64_t)params[dongle_cooldown]) * 1000000)
		return (false);
	return (true);
}

static void	process_request(int dongle_id[2], t_scheduler *scheduler,
		t_heap_node *node_left, t_heap_node *node_right)
{
	t_request	*request_left;
	t_request	*request_right;
	t_heap_node	*n1;
	t_heap_node	*n2;

	request_left = (t_request *)node_left->content;
	request_right = (t_request *)node_right->content;
	if (request_left->coder_id != request_right->coder_id)
		return ;
	if (get_dongle_state(request_left->dongle_l)
		|| get_dongle_state(request_left->dongle_r)
		|| !check_cooldown(request_left, scheduler->params))
		return ;
	n1 = heap_pop(scheduler->heaps[dongle_id[LEFT]], fifo);
	n2 = heap_pop(scheduler->heaps[dongle_id[RIGHT]], fifo);
	set_dongle_state(request_left->dongle_l, true, 0);
	set_dongle_state(request_left->dongle_r, true, 0);
	pthread_mutex_lock(request_left->can_compile_mu);
	*request_left->can_compile = true;
	pthread_cond_signal(request_left->can_compile_cond);
	pthread_mutex_unlock(request_left->can_compile_mu);
	free(n1->content);
	free(n2->content);
	free(n1);
	free(n2);
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
		if (node_left && node_right)
			process_request(dongle_id, scheduler, node_left, node_right);
		i++;
	}
}

void	*scheduler_routine(void *data)
{
	t_scheduler	*scheduler;
	t_request	*request[2];
	t_heap_node	*node_1;
	t_heap_node	*node_2;
	int			dongle[2];

	scheduler = (t_scheduler *)data;
	memset(request, 0, sizeof(t_request *) * 2);
	while (get_sim_state(scheduler->sim_state,
			scheduler->state_mu) == ON)
	{
		who_can_compile(scheduler);
		if (!copy_request(request, scheduler))
		{
			usleep(500);
			continue ;
		}
		node_1 = heap_new_node(request[0]);
		node_2 = heap_new_node(request[1]);
		get_dongle_arr(request[0]->coder_id, scheduler->params, dongle);
		heap_push(scheduler->heaps[dongle[LEFT]], node_1, fifo);
		heap_push(scheduler->heaps[dongle[RIGHT]], node_2, fifo);
		usleep(500);
	}
	return (clean_request_queue(scheduler));
}
