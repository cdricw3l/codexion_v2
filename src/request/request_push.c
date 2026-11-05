/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:12:37 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 16:03:02 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.h"

int request_push(t_request_queue *queue, t_request *request)
{
    t_request *last_node;

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
    return (TRUE);
}