/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:20:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 16:24:00 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

void unit_request_push(void)
{
	START_TEST;

    t_request r1;
    t_request_queue *queue;
    t_request r2;
    t_request r3;


    queue = request_queue_init();
    assert(queue);
    assert(queue->queue);

    r1.coder_id = 0;
    r1.next = NULL;
    assert(request_push(queue, &r1));
    assert(queue->queue_size == 1);
    assert(request_get_last_node(*queue->queue) == &r1);

    r2.coder_id = 1;
    r2.next = NULL;
    assert(request_push(queue, &r2));
    assert(queue->queue_size == 2);
    assert(request_get_last_node(*queue->queue) == &r2);

    r3.coder_id = 2;
    r3.next = NULL;
    assert(request_push(queue, &r3));
    assert(queue->queue_size == 3);
    assert(request_get_last_node(*queue->queue) == &r3);

    assert(!request_push(queue, NULL));
    assert(queue->queue_size == 3);
    assert(!request_push(NULL, NULL));
    assert(queue->queue_size == 3);

    t_request_queue *ptr = NULL;
    assert(!request_destroy_queue(&ptr));
    
    assert(request_destroy_queue(&queue));
	assert(!queue);
    
	END_TEST;	
}