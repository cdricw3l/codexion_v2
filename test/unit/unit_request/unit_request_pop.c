/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_pop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 07:06:22 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 07:18:07 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

static void simple_request_pop(void)
{
	START_TEST;

    t_request_queue *queue;
    t_request r1;
    t_request r2;
    t_request r3;
    t_request r4;
    t_request *request;


    queue = request_queue_init();
    assert(queue);
    assert(queue->queue);

    r1.coder_id = 0;
    r1.request_id = 0;
    r1.next = NULL;
    assert(request_push(queue, &r1));
  
    r2.coder_id = 1;
    r2.request_id = 1;
    r2.next = NULL;
    assert(request_push(queue, &r2));
    

    r3.coder_id = 2;
    r3.request_id = 2;
    r3.next = NULL;
    assert(request_push(queue, &r3));

    r4.coder_id = 3;
    r4.request_id = 3;
    r4.next = NULL;
    assert(request_push(queue, &r4));

    assert(queue->queue_size == 4);
    request = request_pop(queue);
    assert(request == &r1);
    assert(queue->queue_size == 3);

    request = request_pop(queue);
    assert(request == &r2);
    assert(queue->queue_size == 2);

    request = request_pop(queue);
    assert(request == &r3);
    assert(queue->queue_size == 1);

    request = request_pop(queue);
    assert(request == &r4);
    assert(queue->queue_size == 0);
    
    request = request_pop(queue);
    assert(!request);
    assert(queue->queue_size == 0);
    assert(*queue->queue == NULL);

    request = request_pop(NULL);
    assert(!request);
    assert(queue->queue_size == 0);

    assert(request_destroy_queue(&queue));
	assert(!queue);
    
	END_TEST;	
}


void unit_request_pop(void)
{
    simple_request_pop();
}