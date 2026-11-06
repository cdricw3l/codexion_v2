/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_new_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:20:50 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 08:38:31 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_request	*request_new_node(t_coder *coder)
{
	t_request	*request;

	if (!coder || !coder->queue)
		return (NULL);
	request = malloc(sizeof(t_request));
	if (!request)
		return (err_msg(BRED"Error malloc allocation new request"CRESET));
	request->coder_id = coder->coder_id;
	if (pthread_mutex_lock(&coder->queue->queue_mutex))
	{
		free(request);
		return (err_msg(BRED"Error mutex lock new request"CRESET));
	}
	request->request_id = coder->queue->request_counter;
	if (pthread_mutex_unlock(&coder->queue->queue_mutex))
	{
		free(request);
		return (err_msg(BRED"Error mutex unlock new request"CRESET));
	}
	request->can_compile_cond = &coder->can_compile_cond;
	request->can_compile_mu = &coder->can_compile_mu;
	request->can_compile = &coder->can_compile;
	request->next = NULL;
	return (request);
}
