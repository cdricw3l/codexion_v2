/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_new_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:20:50 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 14:59:25 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.h"

t_request *request_new_node(t_coder *coder, t_request_queue *queue)
{
    t_request *request;

    if (!coder || !queue) 
        return (NULL);
    request = malloc(sizeof(t_request));
    if (!request)
        return (err_msg(BRED"Error malloc allocation new request"CRESET));
    request->coder_id = coder->coder_id;
    if (pthread_mutex_lock(&queue->queue_mutex))
    {
        free(request);
        return (err_msg(BRED"Error mutex lock new request"CRESET));
    }
    request->request_id = queue->queue_size;
    if (pthread_mutex_unlock(&queue->queue_mutex))
    {
        free(request);
        return (err_msg(BRED"Error mutex unlock new request"CRESET));
    }
    request->can_compile_cond = coder->can_compile_cond;
    request->can_compile_mu = coder->can_compile_mu;
    request->can_compile = coder->can_compile;
    request->next = NULL;
    return (request);
}
