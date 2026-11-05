/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_destroy_queue.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 16:15:09 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 16:21:15 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.h"

int request_destroy_queue(t_request_queue **q)
{
    t_request_queue *queue;

    if (!q || !*q)
        return (FALSE);
    queue = *q;
    if(queue->queue)
        free(queue->queue);
    if (pthread_mutex_destroy(&queue->queue_mutex))
        err_msg(BRED"Error mutex destruction\n"CRESET);
    free(*q);
    *q = NULL;
    return (TRUE);
}