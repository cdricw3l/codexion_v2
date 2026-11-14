/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_init_queue.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:20:50 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/12 00:41:11 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_request_queue	*request_queue_init(void)
{
	t_request_queue	*request_queue;

	request_queue = malloc(sizeof(t_request_queue));
	if (!request_queue)
		return (err_msg(BRED"Error malloc allocation request struct"CRESET));
	request_queue->queue = malloc(sizeof(t_request *));
	if (!request_queue)
	{
		free(request_queue);
		return (err_msg(BRED"Error malloc allocation request queue"CRESET));
	}
	*request_queue->queue = NULL;
	pthread_mutex_init(&request_queue->queue_mutex, NULL);
	request_queue->queue_size = 0;
	request_queue->request_counter = 1;
	return (request_queue);
}
