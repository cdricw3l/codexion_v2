/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:53:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/18 22:05:28 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	get_sim_state(int *state, pthread_mutex_t *state_mutex)
{
	int	status;

	pthread_mutex_lock(state_mutex);
	status = *state;
	pthread_mutex_unlock(state_mutex);
	return (status);
}

void	set_sim_state(int *state, pthread_mutex_t *state_mutex, int new_state)
{
	pthread_mutex_lock(state_mutex);
	*state = new_state;
	pthread_mutex_unlock(state_mutex);
}

int	fifo(t_heap_node *n1, t_heap_node *n2)
{
	t_request	*request_1;
	t_request	*request_2;

	request_1 = (t_request *)n1->content;
	request_2 = (t_request *)n2->content;
	if (request_1->request_id > request_2->request_id)
		return (TRUE);
	return (FALSE);
}

int	edf(t_heap_node *n1, t_heap_node *n2)
{
	t_request	*request_1;
	t_request	*request_2;

	request_1 = (t_request *)n1->content;
	request_2 = (t_request *)n2->content;
	if (request_1->request_id > request_2->request_id)
		return (TRUE);
	return (FALSE);
}
