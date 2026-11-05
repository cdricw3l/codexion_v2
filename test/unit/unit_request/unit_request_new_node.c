/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_new_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 14:46:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 15:02:19 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

void unit_request_new_node(void)
{
	START_TEST;

    t_coder coder;
    t_request *request;
    t_request_queue *queue;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
    bool can;

    queue = request_queue_init();
    assert(queue);
    assert(queue->queue_size == 0);
    
    can = false;
    coder.coder_id = 0;
    coder.can_compile = &can;
    coder.can_compile_cond = &cond;
    coder.can_compile_mu = &mu;

    request = request_new_node(&coder, queue);
    assert(request);
    assert(request->coder_id == coder.coder_id);
    assert(request->request_id == queue->queue_size);
    assert(request->can_compile_cond == &cond);
    assert(request->can_compile == &can);
    assert(request->can_compile_mu == &mu);
	assert(request->next == NULL);

    free(request);
    
    
    assert(!request_new_node(NULL, queue));
    assert(!request_new_node(&coder, NULL));

    free(queue->queue);
    free(queue);
	END_TEST;	
}