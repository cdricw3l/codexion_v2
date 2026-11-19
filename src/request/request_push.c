/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_push.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:20:50 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/14 12:44:46 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static int	push(t_request_queue *queue, t_request *request)
{
	t_request	*last_node;

	if (!queue || !request)
		return (FALSE);
	if (!*queue->queue)
		*queue->queue = request;
	else
	{
		last_node = request_get_last_node(*queue->queue);
		last_node->next = request;
	}
	queue->queue_size++;
	queue->request_counter++;
	return (TRUE);
}

static t_request	*new_request(t_coder *coder)
{
	t_request	*request;

	request = malloc(sizeof(t_request));
	if (!request)
		return (err_msg(BRED"Error malloc allocation new request"CRESET));
	request->coder_id = coder->coder_id;
	request->dongle_l = coder->dongle_left;
	request->dongle_r = coder->dongle_right;
	request->last_compile = coder->timestamp;
	request->request_id = coder->queue->request_counter;
	request->can_compile_cond = coder->can_compile_cond;
	request->can_compile_mu = coder->can_compile_mu;
	request->can_compile = coder->can_compile;
	request->next = NULL;
	return (request);
}

int	request_push(t_coder *coder)
{
	t_request	*request;
	int			status;

	if (!coder || !coder->queue)
		return (FALSE);
	request = new_request(coder);
	if (!request)
		return (FALSE);
	if (pthread_mutex_lock(&coder->queue->queue_mutex))
	{
		err_msg(BRED"Error mutex lock new request"CRESET);
		return (FALSE);
	}
	status = push(coder->queue, request);
	if (pthread_mutex_unlock(&coder->queue->queue_mutex))
	{
		err_msg(BRED"Error mutex unlock new request"CRESET);
		return (FALSE);
	}
	return (status);
}
