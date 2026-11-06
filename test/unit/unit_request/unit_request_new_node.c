/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_new_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 14:46:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 05:45:34 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

t_coder *get_coder(size_t id, t_request_queue *queue);

void unit_request_new_node(void)
{
	START_TEST;

    t_coder *coder;
    t_request *request;
    t_request_queue *queue;
   

    queue = request_queue_init();
    assert(queue);
    assert(queue->queue_size == 0);
    
    coder = get_coder(0, queue);


    request = request_new_node(coder);
    assert(request);
    assert(request->coder_id == coder->coder_id);
    assert(request->request_id == queue->queue_size);
    
    assert(*request->can_compile == false);
	assert(request->next == NULL);

    free(request);
    free(coder);
    
    assert(!request_new_node(NULL));

    free(queue->queue);
    free(queue);
	END_TEST;	
}