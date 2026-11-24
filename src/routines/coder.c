/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 12:48:06 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 10:46:44 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	action(t_coder *coder, int action)
{
	if (action == COMPILE)
	{
		set_compilation_timestamp(coder, get_now());
		usleep(coder->params[time_to_compile] * 1000);
	}
	if (action == DEBUG)
		usleep(coder->params[time_to_debug] * 1000);
	if (action == REFACTO)
		usleep(coder->params[time_to_refactor] * 1000);
}

static void	coder_action(t_coder *coder)
{
	int64_t	now;
	/* check for One coder */
	if (coder->dongle_left == coder->dongle_right)
		return ;
	pthread_mutex_lock(coder->dongle_right->dongle);
	pthread_mutex_lock(coder->dongle_left->dongle);
	display_action(coder, COMPILE);
	action(coder, COMPILE);
	pthread_mutex_unlock(coder->dongle_right->dongle);
	pthread_mutex_unlock(coder->dongle_left->dongle);
	now = get_now();
	set_dongle_state(coder->dongle_right, false, now);
	set_dongle_state(coder->dongle_left, false, now);
	display_action(coder, DEBUG);
	action(coder, DEBUG);
	display_action(coder, REFACTO);
	action(coder, REFACTO);
}

static void	wait(t_coder *coder)
{
	pthread_mutex_lock(coder->can_compile_mu);
	while (*coder->can_compile == false)
		pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
	*coder->can_compile = false;
	pthread_mutex_unlock(coder->can_compile_mu);
}

void	*coder_routine(void *data)
{
	t_coder		*coder;

	coder = (t_coder *)data;
	wait(coder);
	while (1)
	{
		if (!request_push(coder))
			return (NULL);
		pthread_mutex_lock(coder->can_compile_mu);
		while (*coder->can_compile == false)
			pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
		*coder->can_compile = false;
		pthread_mutex_unlock(coder->can_compile_mu);
		if (!get_sim_state(coder->sim_state, coder->state_mu))
			return (NULL);
		coder_action(coder);
		if (coder->counter++ == coder->params[number_of_compiles_required] - 1)
		{
			set_compilation_timestamp(coder, -1);
			return (NULL);
		}
	}
	return (NULL);
}
