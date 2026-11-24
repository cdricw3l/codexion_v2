/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_clear_queue.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 04:59:44 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 17:32:41 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	request_clear_queue(t_request_queue *queue)
{
	t_request	*root;
	t_request	*tmp;

	//printf("Heap size %ld\n", queue->queue_size);
	if (!queue || !queue->queue || queue->queue_size == 0)
		return ;
	root = *queue->queue;
	while (root)
	{
		tmp = root;
		root = root->next;
		tmp->next = NULL;
		pthread_mutex_lock(tmp->can_compile_mu);
		*tmp->can_compile = true;
		pthread_cond_signal(tmp->can_compile_cond);
		pthread_mutex_unlock(tmp->can_compile_mu);
		free(tmp);
		tmp = NULL;
	}
	queue->queue_size = 0;
	*queue->queue = NULL;
}
