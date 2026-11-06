/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 05:38:34 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 05:58:29 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	request_display(t_request_queue *queue)
{
	t_request	*root;

	printf("\nNumber of request: %ld\n", queue->queue_size);
	root = *queue->queue;
	while (root->next)
	{
		printf("Coder id: %ld\n", root->coder_id);
		printf("Request id: %ld\n", root->request_id);
		root = root->next;
		printf("\n");
	}
}
