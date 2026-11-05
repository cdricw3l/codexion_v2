/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:36:15 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 14:52:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

void unit_request_init(void)
{
	START_TEST;

	t_request_queue *request_queue;

    request_queue = request_queue_init();
    assert(request_queue);
    assert(request_queue->queue);
    assert(request_queue->queue_size == 0);
    assert(!pthread_mutex_lock(&request_queue->queue_mutex));
    assert(!pthread_mutex_unlock(&request_queue->queue_mutex));
    assert(!pthread_mutex_destroy(&request_queue->queue_mutex));
    free(request_queue->queue);
    free(request_queue);
	END_TEST;	
}