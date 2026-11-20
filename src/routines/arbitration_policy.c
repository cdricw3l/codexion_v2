/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitration_policy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 06:30:59 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 06:36:34 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	fifo(t_heap_node *n1, t_heap_node *n2)
{
	t_request	*request_1;
	t_request	*request_2;

	request_1 = (t_request *)n1->content;
	request_2 = (t_request *)n2->content;
	if (request_1->request_id > request_2->request_id)
		return (true);
	return (false);
}

int	edf(t_heap_node *n1, t_heap_node *n2)
{
	t_request	*request_1;
	t_request	*request_2;

	request_1 = (t_request *)n1->content;
	request_2 = (t_request *)n2->content;
	if (request_1->request_id > request_2->request_id)
		return (true);
	return (false);
}
