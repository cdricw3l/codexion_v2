/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:12:37 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 08:36:57 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	request_push(t_request_queue *queue, t_request *request)
{
	t_request	*last_node;

	if (!queue || !request)
		return (FALSE);
	pthread_mutex_lock(&queue->queue_mutex);
	if (!*queue->queue)
		*queue->queue = request;
	else
	{
		last_node = request_get_last_node(*queue->queue);
		last_node->next = request;
	}
	queue->queue_size++;
	queue->request_counter++;
	pthread_mutex_unlock(&queue->queue_mutex);
	return (TRUE);
}
