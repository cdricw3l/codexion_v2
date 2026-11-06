/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_get_queue_size.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 17:03:19 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 05:59:19 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

size_t	request_get_queue_size(t_request_queue *queue)
{
	size_t	size;

	size = 0;
	if (!queue)
		return (size);
	pthread_mutex_lock(&queue->queue_mutex);
	size = queue->queue_size;
	pthread_mutex_unlock(&queue->queue_mutex);
	return (size);
}
