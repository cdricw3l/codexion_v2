/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_clear_queue.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 04:59:44 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 05:56:53 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	request_clear_queue(t_request_queue *queue)
{
	t_request	*root;
	t_request	*tmp;

	if (!queue || !queue->queue)
		return ;
	root = *queue->queue;
	while (root)
	{
		tmp = root;
		root = root->next;
		tmp->next = NULL;
		free(tmp);
	}
	*queue->queue = NULL;
}
