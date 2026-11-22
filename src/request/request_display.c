/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 05:38:34 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:56:13 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	request_display_node(t_request *request)
{
	printf("Coder id: %ld\n", request->coder_id);
	printf("Request id: %ld\n", request->request_id);
	printf("dongle state: %ld\n", request->dongle_l->is_used);
	printf("\n");
}

void	request_display_queue(t_request_queue *queue)
{
	t_request	*root;

	printf("\nNumber of request: %ld\n", queue->queue_size);
	root = *queue->queue;
	while (root->next)
	{
		request_display_node(root);
		root = root->next;
	}
}
