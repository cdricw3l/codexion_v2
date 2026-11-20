/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 12:48:06 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 04:47:58 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	action(t_coder *coder, int action)
{
	if (action == COMPILE)
	{
		set_timestamp(coder);
		usleep(coder->params[time_to_compile] * 1000);
	}
	if (action == DEBUG)
		usleep(coder->params[time_to_debug] * 1000);
	if (action == REFACTO)
		usleep(coder->params[time_to_refactor] * 1000);
}

void set_dongle_state(t_dongles *dongle, int state)
{
	pthread_mutex_lock(&dongle->is_used_mu);
	dongle->is_used = state;
	pthread_mutex_unlock(&dongle->is_used_mu);
}

int get_dongle_state(t_dongles *dongle)
{
	int state;

	pthread_mutex_lock(&dongle->is_used_mu);
	state = dongle->is_used;
	pthread_mutex_unlock(&dongle->is_used_mu);
	return (state);
}

void set_can_compile(t_coder *coder, bool value)
{
	pthread_mutex_lock(coder->can_compile_mu);
	*coder->can_compile = value;
	pthread_mutex_unlock(coder->can_compile_mu);
}

bool get_can_compile(t_coder *coder)
{
	bool value;

	pthread_mutex_lock(coder->can_compile_mu);
	value = *coder->can_compile;
	pthread_mutex_unlock(coder->can_compile_mu);
	return (value);
}

static void	coder_action(t_coder *coder)
{
	pthread_mutex_lock(coder->dongle_right->dongle);
	pthread_mutex_lock(coder->dongle_left->dongle);

	set_dongle_state(coder->dongle_left, ON);
	set_dongle_state(coder->dongle_right, ON);
	
	display_action(coder, COMPILE);
	action(coder, COMPILE);
	pthread_mutex_unlock(coder->dongle_right->dongle);
	pthread_mutex_unlock(coder->dongle_left->dongle);
	set_dongle_state(coder->dongle_left, OFF);
	set_dongle_state(coder->dongle_right, OFF);
	display_action(coder, DEBUG);
	action(coder, DEBUG);
	display_action(coder, REFACTO);
	action(coder, REFACTO);
}

static void wait(t_coder *coder)
{
	pthread_mutex_lock(coder->can_compile_mu);
	while (*coder->can_compile == FALSE)
		pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
	pthread_mutex_unlock(coder->can_compile_mu);
}

void	*coder_routine(void *data)
{
	int			i;
	t_coder		*coder;

	coder = (t_coder *)data;
	
	i = 0;
	wait(coder);
	while (i < coder->params[number_of_compiles_required]
		&& get_sim_state(coder->simulation_state, coder->simulation_state_mu))
	{
		if (!request_push(coder))
		{
			set_sim_state(coder->simulation_state,
				coder->simulation_state_mu, OFF);
			return (NULL);
		}
		pthread_mutex_lock(coder->can_compile_mu);
		while (get_sim_state(coder->simulation_state, coder->simulation_state_mu) && *coder->can_compile == FALSE)
			pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
		/* if a coder burn, the scheduler send signal to all the coder. We dont want to display action, We want to stop the simulation */
		if (get_sim_state(coder->simulation_state, coder->simulation_state_mu))
		{
			//printf("Coder %ld: entering action\n", coder->coder_id);
			coder_action(coder);
			*coder->can_compile = FALSE;
			pthread_mutex_unlock(coder->can_compile_mu);
		}
		else
		{
			pthread_mutex_unlock(coder->can_compile_mu);
			return (NULL);
		}
		i++;
	}

	return (NULL);
}
