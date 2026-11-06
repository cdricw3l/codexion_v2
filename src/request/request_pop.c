/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 06:57:30 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 07:02:50 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_request	*request_pop(t_request_queue *queue)
{
	t_request	*request;

	if (!queue || !queue->queue || queue->queue_size == 0)
		return (NULL);
	pthread_mutex_lock(&queue->queue_mutex);
	request = *queue->queue;
	*queue->queue = request->next;
	queue->queue_size--;
	pthread_mutex_unlock(&queue->queue_mutex);
	return (request);
}
